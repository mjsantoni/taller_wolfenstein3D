//
// Created by andy on 12/2/21.
//

#include "client/graphics/texture_manager.h"

TextureManager::TextureManager(SdlWindow& _window,
                               ObjectInfoProvider& _info_provider) :
    window(_window),
    info_provider(_info_provider) {
  std::vector<Area> fake_vector;
  auto* fake_texture = (SdlTexture*) nullptr;
  textures.push_back(fake_texture);
  areas_vector.push_back(fake_vector);
  for (int object_type = ROCK_WALL; object_type <= UI_PLAYER_FACE;
       ++object_type) {
    ObjectInfo object_info = info_provider.getObjectInfo(object_type);
    std::string image_path = object_info.getImagePath();
    auto* texture = new SdlTexture(window, image_path);
    std::vector<Area> areas;
    if (object_info.isSprite()) {
      areas = getAllSpriteAreas(object_info);
      texture = new SdlSprite(window, object_info);
    } else
      areas = getSingleImageArea(texture);
    textures.push_back(texture);
    areas_vector.push_back(areas);
  }
}

std::vector<Area> TextureManager::getAllSpriteAreas(ObjectInfo& object_info) {
  SdlSprite sprite(window, object_info);
  return sprite.getAllTheAreas();
}

std::vector<Area> TextureManager::getSingleImageArea(SdlTexture* texture) {
  std::vector<Area> single_area_vector;
  Area area = texture->getTextureArea();
  single_area_vector.push_back(area);
  return single_area_vector;
}

SdlTexture* TextureManager::getTextureFromObjectType(int object_type) {
  return textures[object_type];
}

Area TextureManager::getImageAreaFromObjectType(int object_type) {
  return areas_vector[object_type][0];
}

Area TextureManager::getAreaForEnemySprite(int object_type,
                                           int current_animation_no) {
  return areas_vector[object_type][current_animation_no];
}

Area TextureManager::getAreaForWeapon(int object_type,
                                      int current_animation_no) {
  return areas_vector[object_type][current_animation_no];
}

TextureManager::~TextureManager() {
  for (auto* texture : textures) {
    free(texture);
  }
}


