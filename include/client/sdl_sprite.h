//
// Created by andy on 26/11/20.
//

#ifndef TP_WOLFENSTEIN_SDLSPRITE_H
#define TP_WOLFENSTEIN_SDLSPRITE_H


#include <vector>
#include <server/game/map.h>
#include "sdl_texture.h"
#include "sdl_exception.h"

class SdlSprite : public SdlTexture {
public:
    SdlSprite(std::string file_name, int width, int height, int cols, int rows,
              int h_padding, int v_padding);
    SDL_Texture* loadNextTexture(SDL_Renderer* renderer, Area& srcArea);
    SDL_Texture* loadTexture(SDL_Renderer* renderer, Area& srcArea,
                             int sprite_number);
    void setPadding(int horizontal_padding, int vertical_padding);
private:
    int h_padding = 0;
    int v_padding = 0;
    int whole_width;
    int whole_height;
    int rows;
    int cols;
    bool already_loaded = false;
    int each_img_width;
    int each_img_height;
    std::vector<Area> dimensions;
    std::map<int, Area> dimensions_map;
    int current_pos = 0;
    void loadIndividualDimensions();
    void fillDimensions(Area& source_area, Area& empty_area);

};


#endif //TP_WOLFENSTEIN_SDLSPRITE_H
