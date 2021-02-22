//
// Created by andy on 26/11/20.
//

#include <client/graphics/images.h>
#include "client/graphics/sdl_sprite.h"

SdlSprite::SdlSprite(SdlWindow& window, ObjectInfo& object_info) :
    SdlTexture(window, object_info.getImagePath()) {
  whole_width = object_info.getImageWidth();
  whole_height = object_info.getImageHeight();
  cols = object_info.getSpriteCols();
  rows = object_info.getSpriteRows();
  h_padding = object_info.getSpriteHPadding();
  v_padding = object_info.getSpriteVPadding();
  object_type = object_info.getObjectType();
  loadIndividualDimensions();
}

void SdlSprite::loadIndividualDimensions() {
  each_img_width = whole_width / cols - h_padding / 2;
  each_img_height = whole_height / rows - v_padding / 2;
  int x = 0;
  int y = 0;
  if (object_type == ENEMY_DOG) {
    x = h_padding / 2;
    y = v_padding / 2;
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      Area area(x, y, each_img_width, each_img_height);
      dimensions.push_back(area);
      x += h_padding / 2 + each_img_width;
    }
    x = 0;
    y += v_padding / 2 + each_img_height;
  }
}

void SdlSprite::fillDimensions(Area& source_area, Area& empty_area) {
  empty_area.setX(source_area.getX());
  empty_area.setY(source_area.getY());
  empty_area.setWidth(source_area.getWidth());
  empty_area.setHeight(source_area.getHeight());
}

std::vector<Area> SdlSprite::getAllTheAreas() {
  return dimensions;
}

void SdlSprite::render(Area& screen_area, int sprite_no) {
  Area image_area = dimensions[sprite_no];
  SdlTexture::render(image_area, screen_area);
}
