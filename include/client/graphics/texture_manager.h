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
    std::vector<SDL_Texture*> textures;
    std::vector<Area> areas;
    ObjectInfoProvider& info_provider;
    SdlWindow& window;
public:
    TextureManager(SdlWindow& _window, ObjectInfoProvider& _info_provider);
    SDL_Texture *getImageFromObjectType(int object_type);
    Area getImageAreaFromObjectType(int object_type);
};


#endif //TP_WOLFENSTEIN_TEXTUREMANAGER_H
