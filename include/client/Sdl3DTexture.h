//
// Created by andy on 28/11/20.
//

#ifndef TP_WOLFENSTEIN_SDL3DTEXTURE_H
#define TP_WOLFENSTEIN_SDL3DTEXTURE_H

#include "SdlTexture.h"

class Sdl3DTexture : public SdlTexture {
public:
    Sdl3DTexture(std::string file_name);
    SDL_Texture* load3DTexture(SDL_Renderer* renderer, Area& src_area);
    SDL_Texture* load3DTextureForColumn(SDL_Renderer* renderer, Area& src_area);
    void fillDimensions(Area& area) override;

};


#endif //TP_WOLFENSTEIN_SDL3DTEXTURE_H
