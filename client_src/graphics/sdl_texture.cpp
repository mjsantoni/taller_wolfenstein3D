//
// Created by andy on 26/11/20.
//

#include "client/graphics/sdl_texture.h"
#include <SDL_image.h>


SdlTexture::SdlTexture(SdlWindow &window,
                       const std::string &_file_name) :
        renderer(window.getRenderer()), file_name(_file_name) {
    texture = loadTexture(_file_name);
}

SdlTexture::SdlTexture() : file_name("fake_route") { // FAKE TEXTURE, solo para ocupar un espacio del vector del texture manager
}

SdlTexture& SdlTexture::operator=(SdlTexture&& other) noexcept {
    if (this == &other)
        return *this;
    if (this->texture)
        free(this->texture);
    if (this->renderer)
        free(this->renderer);

    this->renderer = other.renderer;
    this->texture = other.texture;
    this->file_name = std::move(other.file_name);

    other.texture = nullptr;
    other.renderer = nullptr;

    return *this;
}

SdlTexture::~SdlTexture() {
    SDL_DestroyTexture(texture);
}

SDL_Texture* SdlTexture::loadTexture(const std::string& _file_name) {
    SDL_Texture* _texture = IMG_LoadTexture(renderer, _file_name.c_str());
    if (!_texture)
        throw SdlException("Error en la carga de la textura", SDL_GetError());
    return _texture;
}

void SdlTexture::render(Area& dest) {
    Area src = getTextureArea();
    SDL_Rect sdlSrc = {
            src.getX(), src.getY(), src.getWidth(), src.getHeight()
    };
    // donde se pega, y si hay diferencia de dimensiones
    SDL_Rect sdlDest = {
            dest.getX(), dest.getY(), dest.getWidth(), dest.getHeight()
    };
    SDL_RenderCopy(renderer, texture, &sdlSrc, &sdlDest);
}

void SdlTexture::render(Area& src, Area& dest) {
    SDL_Rect sdlSrc = {
            src.getX(), src.getY(), src.getWidth(), src.getHeight()
    };
    // donde se pega, y si hay diferencia de dimensiones
    SDL_Rect sdlDest = {
            dest.getX(), dest.getY(), dest.getWidth(), dest.getHeight()
    };
    SDL_RenderCopy(renderer, texture, &sdlSrc, &sdlDest);
}

Area SdlTexture::getTextureArea() {
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    return Area{0, 0, width, height};
}

SDL_Texture* SdlTexture::getTexture() {
    return texture;
}
SdlTexture::SdlTexture(SdlTexture&& other) noexcept {
    this->texture = other.texture;
    this->renderer = other.renderer;
    this->file_name = other.file_name;
    other.renderer = nullptr;
    other.texture = nullptr;
}
