//
// Created by andy on 10/2/21.
//

#include "client/graphics/ray_casting_assistant.h"

RayCastingAssistant::RayCastingAssistant(SdlWindow& _window,
                                         TextureManager& _texture_manager) :
    window(_window),
    texture_manager(_texture_manager) {
}

void RayCastingAssistant::drawFloor(int x_pos, int wall_posY, int wall_height) {
  int fsp_for_column = wall_posY + wall_height;
  int fh_for_column = screen_height - fsp_for_column;
  Area area(x_pos, fsp_for_column, 1, fh_for_column);
  window.drawRectangle(area, 123, 123, 123, 0);
}

void RayCastingAssistant::drawCeiling(int x_pos, int y_pos) {
  Area area(x_pos, 0, 1, y_pos);
  window.drawRectangle(area, 60, 60, 60, 0);
}

void RayCastingAssistant::setDimensions(int width, int height) {
  screen_width = width;
  screen_height = height;
  proj_plane_distance = (int) (((double) screen_width / 2) / tan(FOV / 2));
}

double RayCastingAssistant::findWallHeight(double distance) {
  auto height_proportion = (double) WALL_HEIGHT / distance;
  return (height_proportion * proj_plane_distance); // altura muro
}

int RayCastingAssistant::findWallStartingPoint(double wall_height) {
  return (int(screen_height / 2) - int(wall_height / 2));
}

void RayCastingAssistant::putWall(int ray_no, ObjectInfo& object_info) {
  int object_type = object_info.getObjectType();
  SdlTexture* texture = texture_manager.getTextureFromObjectType(object_type);
  Area image_area = texture->getTextureArea();
  image_area.setX((int) (object_info.getHitGridPos() * image_area.getWidth()));
  image_area.setWidth(image_area.getWidth() / map_grid_size);
  Area screen_area = assembleScreenArea(ray_no, object_info);
  texture->render(image_area, screen_area);
}

Area RayCastingAssistant::assembleScreenArea(int ray_no, ObjectInfo& object_info) {
  double distance = object_info.getHitDistance();
  double wall_height = findWallHeight(distance);
  int wall_starting_point = findWallStartingPoint(wall_height);
  double screen_column_starting_point = wall_starting_point + wall_height;
  auto column_height =
      double(wall_starting_point - screen_column_starting_point);

  //column_height = (screen_column_starting_point + column_height) >
  //SCREEN_DRAWING_HEIGHT? SCREEN_DRAWING_HEIGHT - screen_column_starting_point:
  //column_height;
  Area screen_area(
      ray_no, (int) screen_column_starting_point, 1, (int) column_height
  );
  return screen_area;
}

void RayCastingAssistant::putFloorAndCeiling(int ray_no, ObjectInfo& object_info) {
  Area screen_area = assembleScreenArea(ray_no, object_info);
  drawFloor(ray_no, screen_area.getY(), screen_area.getHeight());
  drawCeiling(ray_no, screen_area.getY());
}
