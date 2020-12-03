//
// Created by andy on 26/11/20.
//

#include <SDL.h>
#include "SdlWindow.h"
#include "../Exceptions/SdlException.h"
#include "../Game/Wall.h"
#include "../Game/Wall_3d.h"

#define PROJECTION_PLANE_width 320
#define PROJECTION_PLANE_height 200

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

void SdlWindow::put3DColumn(int ray_no, DrawingInfo drawing_info){
    Area image_area;
    image_area.setX(ray_no*width/PROJECTION_PLANE_width);
    SDL_Texture* texture = assembleImageArea(drawing_info, image_area);
    Area screen_area = assembleScreenArea(ray_no, drawing_info);
    putTextureAt(texture, image_area, screen_area);
    drawFloor(ray_no, screen_area.getY(), screen_area.getHeight());
    drawCeiling(ray_no, screen_area.getY());
    SDL_DestroyTexture(texture);
}

SDL_Texture* SdlWindow::assembleImageArea(DrawingInfo drawing_info,
                                          Area& image_area) {
    //image_area.setX(drawing_info.object_x_pos);
    SDL_Texture* texture;
    switch (drawing_info.object_type) {
        case 1: {
            Wall_3d wall("../Resources/wall_3.gif");
            texture = wall.getImageForColumn(renderer, image_area);
            break;
        }
        case 2: {
            Wall_3d wall("../Resources/wall_3.gif");
            texture = wall.getImageForColumn(renderer, image_area);
            break;
        }
    }
    int real_width = 2;
    image_area.setWidth(real_width);
    //printf("Se copiara una pared desde: (%d, %d) con ancho de %d y altura de %d\n", image_area.getX(), image_area.getY(), image_area.getWidth(), image_area.getHeight());
    return texture;
}

Area SdlWindow::assembleScreenArea(int ray_no, DrawingInfo& drawing_info) {
    int width_factor = width/PROJECTION_PLANE_width;
    int distance = (int) drawing_info.hit_distance;
    int col_height = 0;
    int col_starting_point = findColumnStartingPoint(distance, col_height);
    Area screen_area(
            ray_no*width_factor,col_starting_point, width_factor, col_height
            );
    //printf("Rayo %d:Se coloca una pared a distancia %d, en (%d, %d), con un ancho de %d y altura de %d\n",
           //ray_no, distance, ray_no*width_factor, col_starting_point, width_factor, col_height);
    return screen_area;
}

int SdlWindow::findColumnStartingPoint(int distance, int& col_height) {
    auto slice_proportion = (double) 64/distance;
    int slice_projection = (int) (slice_proportion*255);
    int col_starting_point = (height - slice_projection)/2;
    col_height = slice_projection;
    return col_starting_point;
}

int SdlWindow::getWidth() {
    return width;
}

void SdlWindow::drawFloor(int x_pos, int wall_posY, int wall_height) {
    int width_factor = width/PROJECTION_PLANE_width;
    int floor_starting_point = wall_posY + wall_height;
    int floor_height = height - floor_starting_point;
    SDL_Rect floor_rect = {
            x_pos*width_factor, floor_starting_point, width_factor, floor_height
    };
    SDL_SetRenderDrawColor(renderer, 123, 123, 123, 0);
    SDL_RenderFillRect(renderer, &floor_rect);
}

void SdlWindow::drawCeiling(int x_pos, int y_pos) {
    int width_factor = width/PROJECTION_PLANE_width;
    SDL_Rect ceiling_rect = {
            x_pos*width_factor, 0, width_factor, y_pos
    };
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 0);
    SDL_RenderFillRect(renderer, &ceiling_rect);
}

