//
// Created by andy on 26/11/20.
//

#ifndef TP_WOLFENSTEIN_SDLSPRITE_H
#define TP_WOLFENSTEIN_SDLSPRITE_H


#include <vector>
#include <server/game/map.h>
#include "sdl_texture.h"
#include "client/sdl_exception.h"
#include <SDL_image.h>
#include <client/object_info.h>

class SdlSprite : public SdlTexture {
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
    int object_type;
    std::vector<Area> dimensions;
    std::map<int, Area> dimensions_map;
    int current_pos = 0;
    void loadIndividualDimensions();
    void fillDimensions(Area& source_area, Area& empty_area);

public:
    SdlSprite(SdlWindow &window, ObjectInfo &object_info);
    SDL_Texture* loadNextTexture(SDL_Renderer* renderer, Area& srcArea);
    SDL_Texture* loadTexture(SDL_Renderer* renderer, Area& srcArea,
                             int sprite_number);
    void setPadding(int horizontal_padding, int vertical_padding);
    std::vector<Area> getAllTheAreas();
    Area getTextureArea(int sprite_no);
    void render(Area& screen_area, int sprite_no);
};


#endif //TP_WOLFENSTEIN_SDLSPRITE_H
