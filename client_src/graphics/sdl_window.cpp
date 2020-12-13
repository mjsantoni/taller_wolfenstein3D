//
// Created by andy on 26/11/20.
//

#include <SDL.h>
#include "client/sdl_window.h"

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

void SdlWindow::put3DColumn(int ray_no, DrawingInfo drawing_info){
    Area image_area;
    //image_area.setX(ray_no*width/PROJECTION_PLANE_width);
    SDL_Texture* texture = drawer.drawWall(drawing_info, image_area);
    Area screen_area = assembleScreenArea(ray_no, drawing_info);
    putTextureAt(texture, image_area, screen_area);
    drawer.drawFloor(ray_no, screen_area.getY(), screen_area.getHeight());
    drawer.drawCeiling(ray_no, screen_area.getY());
    SDL_DestroyTexture(texture);
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

void SdlWindow::put3DObject(double distance,
                            int max_dist_x,
                            int max_dist_y,
                            double beta,
                            Drawable& object){
    Area image_area;
    DrawingInfo drawing_info;
    drawing_info.hit_distance = distance;
    drawing_info.object_type = object.getObjectType();
    drawing_info.hit_grid_pos = 0;
    SDL_Texture* texture = drawer.drawImage(drawing_info, image_area);
    Area screen_area = assembleScreenArea(drawing_info, distance, max_dist_x,
                                          max_dist_y, beta);
    putTextureAt(texture, image_area, screen_area);
    SDL_DestroyTexture(texture);
}

Area SdlWindow::assembleScreenArea(DrawingInfo& drawing_info,
                                   double distance,
                                   int max_dist_x,
                                   int max_dist_y,
                                   double beta) {
    Area screen_area;
    drawer.findObjectProportions(drawing_info,distance, max_dist_x, max_dist_y,
                                 beta, screen_area);
    return screen_area;
}

