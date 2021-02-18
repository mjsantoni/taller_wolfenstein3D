//
// Created by andy on 12/2/21.
//

#ifndef TP_WOLFENSTEIN_TEXTUREMANAGER_H
#define TP_WOLFENSTEIN_TEXTUREMANAGER_H

#include <SDL_render.h>
#include <vector>
#include <client/graphics/images.h>
#include <client/object_info_provider.h>
#include <client/drawable.h>
#include <client/graphics/sdl_texture.h>
#include "sdl_window.h"

class TextureManager {
private:
    std::vector<SdlTexture*> textures;
    std::vector<std::vector<Area>> areas_vector;
    ObjectInfoProvider& info_provider;
    SdlWindow& window;
public:
    TextureManager(SdlWindow& _window, ObjectInfoProvider& _info_provider);
    SdlTexture* getTextureFromObjectType(int object_type);
    Area getImageAreaFromObjectType(int object_type);
    std::vector<Area> getSingleImageArea(SdlTexture* texture);
    std::vector<Area> getAllSpriteAreas(ObjectInfo &object_info);
    Area getAreaForEnemySprite(int object_type, int current_animation_no);
    Area getAreaForWeapon(int object_type, int current_animation_no);
};


#endif //TP_WOLFENSTEIN_TEXTUREMANAGER_H
