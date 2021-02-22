//
// Created by andy on 10/2/21.
//

#ifndef TP_WOLFENSTEIN_RAY_CASTER_DRAWING_ASSISTANT_H
#define TP_WOLFENSTEIN_RAY_CASTER_DRAWING_ASSISTANT_H

#include <SDL_render.h>
#include <client/object_info.h>
#include <client/graphics/area.h>
#include <client/graphics/sdl_texture.h>
#include <client/graphics/sdl_window.h>
#include <map>
#include "texture_manager.h"
#include "screen_drawing_values.h"

class RayCasterDrawingAssistant {
 private:
  SdlWindow& window;
  TextureManager& texture_manager;
  int screen_width;
  int screen_height;
  int map_grid_size = 64;
  int proj_plane_distance;
 public:
  RayCasterDrawingAssistant(SdlWindow& _window, TextureManager& _texture_manager);
  void drawFloor(int x_pos, int wall_posY, int wall_height);
  void drawCeiling(int x_pos, int y_pos);
  double findWallHeight(double distance) const;
  void putWall(int ray_no, ObjectInfo& object_info);
  void setDimensions(int width, int height);
  Area assembleScreenArea(int ray_no, ObjectInfo& object_info) const;
  void putFloorAndCeiling(int ray_no, ObjectInfo& object_info);
  int findWallStartingPoint(double wall_height) const;
};

#endif //TP_WOLFENSTEIN_RAY_CASTER_DRAWING_ASSISTANT_H
