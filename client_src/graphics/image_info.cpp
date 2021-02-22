//
// Created by andy on 10/12/20.
//

#include "client/graphics/image_info.h"

int ImageInfo::getImageWidth() const {
  return image_width;
}

void ImageInfo::setImageWidth(int _image_width) {
  image_width = _image_width;
}

int ImageInfo::getImageHeight() const {
  return image_height;
}

void ImageInfo::setImageHeight(int _image_height) {
  image_height = _image_height;
}

std::string ImageInfo::getObjectName() const {
  return object_name;
}

void ImageInfo::setObjectName(std::string _object_name) {
  object_name = std::move(_object_name);
}

std::string ImageInfo::getImagePath() const {
  return image_path;
}

void ImageInfo::setImagePath(std::string _image_path) {
  image_path = std::move(_image_path);
}

int ImageInfo::getSpriteAnimationNo() const {
  return sprite_animation_no;
}

void ImageInfo::setSpriteAnimationNo(int _sprite_animation_no) {
  sprite_animation_no = _sprite_animation_no;
}

int ImageInfo::getSpriteRows() const {
  return sprite_rows;
}

void ImageInfo::setSpriteRows(int _sprite_rows) {
  sprite_rows = _sprite_rows;
}

int ImageInfo::getSpriteCols() const {
  return sprite_cols;
}

void ImageInfo::setSpriteCols(int _sprite_cols) {
  sprite_cols = _sprite_cols;
}

int ImageInfo::getSpriteHPadding() const {
  return sprite_h_padding;
}

void ImageInfo::setSpriteHPadding(int _sprite_h_padding) {
  sprite_h_padding = _sprite_h_padding;
}

int ImageInfo::getSpriteVPadding() const {
  return sprite_v_padding;
}

void ImageInfo::setSpriteVPadding(int _sprite_v_padding) {
  sprite_v_padding = _sprite_v_padding;
}

bool ImageInfo::isSprite() const {
  return is_sprite;
}

void ImageInfo::setIsSprite(bool _is_sprite) {
  is_sprite = _is_sprite;
}
