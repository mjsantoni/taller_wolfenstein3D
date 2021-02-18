//
// Created by andy on 26/11/20.
//

#ifndef TP_WOLFENSTEIN_SDL_TEXTURE_H
#define TP_WOLFENSTEIN_SDL_TEXTURE_H


#include <string>
#include <SDL_render.h>
#include "area.h"
#include "client/sdl_exception.h"
#include <client/object_info.h>


class SdlTexture {
public:
    SdlTexture(SdlTexture&) = delete;
    SdlTexture(SdlTexture&&);
    SdlTexture();
    SdlTexture(SDL_Renderer *renderer, std::string file_name);
    SdlTexture(SDL_Renderer *renderer, ObjectInfo &object_info);
    ~SdlTexture();
    SDL_Texture* loadTexture(SDL_Renderer* _renderer, Area& srcArea);
    SDL_Texture* getTexture();
    Area getTextureArea();
    void operator=(const SdlTexture&) = delete;
    SdlTexture& operator=(SdlTexture&&) noexcept;
    void render(Area &src, Area &dest);
    void render(Area &dest);
protected:
    std::string file_name;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    int cols = 1;
    int rows = 1;
    int h_padding;
    int v_padding;

    void getDimensions(SDL_Texture* new_texture);
    virtual void fillDimensions(Area& area);
private:
    int width = 0;
    int height = 0;
    SDL_Texture *loadTexture(const std::string &file_name);
};


#endif //TP_WOLFENSTEIN_SDL_TEXTURE_H
