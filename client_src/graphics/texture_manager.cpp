//
// Created by andy on 12/2/21.
//

#include "client/graphics/texture_manager.h"

TextureManager::TextureManager(SdlWindow& _window,
                               ObjectInfoProvider& _info_provider) :
                               window(_window),
                               info_provider(_info_provider) {
    std::vector<Area> fake_vector;
    textures.push_back((SDL_Texture*) nullptr);
    areas_vector.push_back(fake_vector);
    for (int object_type = GRAY_WALL; object_type < MISC_TABLE; ++object_type) {
        ObjectInfo object_info = info_provider.getObjectInfo(object_type);
        std::string image_path = object_info.getImagePath();
        SdlTexture texture(image_path);
        std::vector<Area> areas;
        if (object_info.isSprite())
            areas = getAllSpriteAreas(object_info);
        else
            areas = getSingleImageArea(object_info);
        SDL_Texture* image = texture.getTexture(window.getRenderer());
        textures.push_back(image);
        areas_vector.push_back(areas);
    }
}

std::vector<Area> TextureManager::getAllSpriteAreas(ObjectInfo& object_info) {
    SdlSprite sprite(object_info);
    return sprite.getAllTheAreas();
}

std::vector<Area> TextureManager::getSingleImageArea(ObjectInfo& object_info) {
    std::vector<Area> single_area_vector;
    //Area area{0, 0, object_info.getImageWidth(),object_info.getImageHeight()};
    Area area;
    SdlTexture texture(object_info.getImagePath());
    texture.loadTexture(window.getRenderer(), area);
    single_area_vector.push_back(area);
    return single_area_vector;
}

SDL_Texture* TextureManager::getImageFromObjectType(int object_type) {
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


