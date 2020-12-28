//
// Created by andy on 26/11/20.
//

#include <SDL.h>
#include "client/sdl_window.h"

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
    drawer.setRenderer(renderer, width, height);
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

void SdlWindow::fillSquare(Area area) {
    SDL_Rect rect = {
            area.getX(), area.getY(), area.getWidth(), area.getHeight()
    };
    SDL_SetRenderDrawColor(renderer, 152, 0, 136, 0);
    SDL_RenderFillRect(renderer, &rect);
}

void SdlWindow::displayFullImage(SdlTexture& texture) {
    Area src_area;
    texture.loadTexture(renderer, src_area);
    Area dest_area(0, 0, width, height);
    putTextureAt(texture.getTexture(), src_area, dest_area);
}

void SdlWindow::restore() {
    SDL_RestoreWindow(window);
}

void SdlWindow::putWall(int ray_no, DrawingInfo& drawing_info) {
    Area image_area;
    SDL_Texture* texture = drawer.drawWall(drawing_info, image_area);
    Area screen_area = drawer.assembleScreenArea(ray_no, drawing_info);
    putTextureAt(texture, image_area, screen_area);
    SDL_DestroyTexture(texture);
}

void SdlWindow::putFloorAndCeiling(int ray_no, DrawingInfo& drawing_info) {
    Area screen_area = drawer.assembleScreenArea(ray_no, drawing_info);
    drawer.drawFloor(ray_no, screen_area.getY(), screen_area.getHeight());
    drawer.drawCeiling(ray_no, screen_area.getY());
}


int SdlWindow::getWidth() {
    return width;
}

void SdlWindow::put3DObject(double distance,
                            double pl_ob_angle,
                            Drawable& object){
    Area image_area;
    DrawingInfo drawing_info;
    drawing_info.hit_distance = distance;
    drawing_info.object_type = object.getObjectType();
    drawing_info.hit_grid_pos = 0;
    SDL_Texture* texture = drawer.drawImage(drawing_info, image_area);
    Area screen_area = drawer.assembleScreenArea(drawing_info, distance,
                                                 pl_ob_angle);
    printf("Nombre de objeto: %s\n", drawing_info.object_name.c_str());
    printf("Distancia: %f\n", distance);
    printf("Pos x: %d\n", screen_area.getX());
    printf("Pos y: %d\n", screen_area.getY());
    printf("Altura: %d\n", screen_area.getHeight());
    printf("Ancho: %d\n", screen_area.getWidth());
    putTextureAt(texture, image_area, screen_area);
    SDL_DestroyTexture(texture);
}

