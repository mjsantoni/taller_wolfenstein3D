//
// Created by andy on 26/11/20.
//

#ifndef TP_WOLFENSTEIN_SDLSPRITE_H
#define TP_WOLFENSTEIN_SDLSPRITE_H


#include <vector>
#include "sdl_texture.h"

class SdlSprite : public SdlTexture {
public:
    SdlSprite(std::string file_name, int rows, int cols);
    SDL_Texture* loadNextTexture(SDL_Renderer* renderer, Area& srcArea);
private:
    int rows;
    int cols;
    bool already_loaded = false;
    int each_img_width;
    int each_img_height;
    std::vector<Area> dimensions;
    int current_pos = 0;
    void getIndividualDimensions(SDL_Texture* new_texture);
    void fillDimensions(Area& srcArea);

};


#endif //TP_WOLFENSTEIN_SDLSPRITE_H
