//
// Created by andy on 26/11/20.
//

#include <SDL.h>
#include "client/graphics/sdl_window.h"

#define PROJECTION_PLANE_width 320
#define PROJECTION_PLANE_height 200
#define GRID_SIZE 64

SdlWindow::SdlWindow(int width, int height) : width(width), height(height) {
    int error_code;
    error_code = SDL_Init(SDL_INIT_VIDEO);
    if (error_code)
        throw SdlException("Error en la inicializacion: ", SDL_GetError());
    error_code = SDL_CreateWindowAndRenderer(
            width, height, SDL_RENDERER_ACCELERATED, &window, &renderer
    );
    if (error_code)
        throw SdlException("Error al crear la ventana", SDL_GetError());
    width_prop = double (width)/320;
    height_prop = double (height)/200;
}

SdlWindow::~SdlWindow() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        this->renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        this->window = nullptr;
    }
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
    SDL_RenderClear(renderer);
}

void SdlWindow::fill() {
    fill(152, 0, 136, 0);
}

void SdlWindow::render() {
    SDL_RenderPresent(renderer);
}

SDL_Renderer* SdlWindow::getRenderer() const {
    return renderer;
}

SDL_Surface* SdlWindow::getSurface() const {
    return SDL_GetWindowSurface(window);
}

void SdlWindow::putTextureAt(SDL_Texture* texture, Area src, Area dest) {
    SDL_Rect sdlSrc = {
            src.getX(), src.getY(), src.getWidth(), src.getHeight()
    };
    // donde se pega, y si hay diferencia de dimensiones
    SDL_Rect sdlDest = {
            dest.getX(), dest.getY(), dest.getWidth(), dest.getHeight()
    };
    SDL_RenderCopy(renderer, texture, &sdlSrc, &sdlDest);
}

void SdlWindow::fillArea(Area area, int r, int g, int b, int a) {
    SDL_Rect rect = {
            area.getX(), area.getY(), area.getWidth(), area.getHeight()
    };
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &rect);
}

void SdlWindow::displayFullImage(SdlTexture& texture) {
    Area src_area;
    SDL_Texture* image = texture.loadTexture(renderer, src_area);
    Area dest_area(0, 0, width, height);
    putTextureAt(image, src_area, dest_area);
}

void SdlWindow::restore() {
    SDL_RestoreWindow(window);
}

int SdlWindow::getWidth() {
    return width;
}

int SdlWindow::getHeight() {
    return height;
}

void SdlWindow::drawRectangle(Area& area, int r, int g, int b, int a) {
    SDL_Rect floor_rect = {
            area.getX(), area.getY(), area.getWidth(), area.getHeight()
    };
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &floor_rect);
}

void SdlWindow::loadImage(SDL_Texture* texture,
                          Area& image_area,
                          Area& screen_area) {
    putTextureAt(texture, image_area, screen_area);
}






