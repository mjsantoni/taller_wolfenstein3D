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

 public:
  SdlSprite(SdlWindow& window, ObjectInfo& object_info);
  std::vector<Area> getAllTheAreas();
  void render(Area& screen_area, int sprite_no);
};

#endif //TP_WOLFENSTEIN_SDLSPRITE_H
