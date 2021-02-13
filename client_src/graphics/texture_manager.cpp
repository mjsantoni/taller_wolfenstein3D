//
// Created by andy on 12/2/21.
//

#include "client/graphics/texture_manager.h"

TextureManager::TextureManager(SdlWindow& _window,
                               ObjectInfoProvider& _info_provider) :
                               window(_window),
                               info_provider(_info_provider) {
    Area fake_area;
    textures.push_back((SDL_Texture*) nullptr);
    areas.push_back(fake_area);
    for (int object_type = GRAY_WALL; object_type < MISC_TABLE; ++object_type) {
        ObjectInfo object_info = info_provider.getObjectInfo(object_type);
        std::string image_path = object_info.getImagePath();
        SdlTexture texture(image_path);
        Area area;
        SDL_Texture* image = texture.loadTexture(window.getRenderer(), area);
        textures.push_back(image);
        areas.push_back(area);
    }
}

SDL_Texture* TextureManager::getImageFromObjectType(int object_type) {
    return textures[object_type];
}

Area TextureManager::getImageAreaFromObjectType(int object_type) {
    return areas[object_type];
}


