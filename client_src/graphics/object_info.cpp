//
// Created by andy on 22/1/21.
//

#include "client/object_info.h"

int ObjectInfo::getImageWidth() const {
  return image_info.getImageWidth();
}

void ObjectInfo::setImageWidth(int image_width) {
  image_info.setImageWidth(image_width);
}

int ObjectInfo::getImageHeight() const {
  return image_info.getImageHeight();
}

void ObjectInfo::setImageHeight(int image_height) {
  image_info.setImageHeight(image_height);
}

std::string ObjectInfo::getObjectName() const {
  return image_info.getObjectName();
}

void ObjectInfo::setObjectName(std::string _object_name) {
  object_name = std::move(_object_name);
}

std::string ObjectInfo::getImagePath() const {
  return image_info.getImagePath();
}

void ObjectInfo::setImagePath(std::string image_path) {
  image_info.setImagePath(std::move(image_path));
}

int ObjectInfo::getSpriteAnimationNo() const {
  return image_info.getSpriteAnimationNo();
}

void ObjectInfo::setSpriteAnimationNo(int sprite_animation_no) {
  image_info.setSpriteAnimationNo(sprite_animation_no);
}

int ObjectInfo::getSpriteRows() const {
  return image_info.getSpriteRows();
}

void ObjectInfo::setSpriteRows(int sprite_rows) {
  image_info.setSpriteRows(sprite_rows);
}

int ObjectInfo::getSpriteCols() const {
  return image_info.getSpriteCols();
}

void ObjectInfo::setSpriteCols(int sprite_cols) {
  image_info.setSpriteCols(sprite_cols);
}

int ObjectInfo::getSpriteHPadding() const {
  return image_info.getSpriteHPadding();
}

void ObjectInfo::setSpriteHPadding(int sprite_h_padding) {
  image_info.setSpriteHPadding(sprite_h_padding);
}

int ObjectInfo::getSpriteVPadding() const {
  return image_info.getSpriteVPadding();
}

void ObjectInfo::setSpriteVPadding(int sprite_v_padding) {
  image_info.setSpriteVPadding(sprite_v_padding);
}

bool ObjectInfo::isSprite() const {
  return image_info.isSprite();
}

void ObjectInfo::setIsSprite(bool is_sprite) {
  image_info.setIsSprite(is_sprite);
}

int ObjectInfo::getObjectType() const {
  return object_type;
}

void ObjectInfo::setObjectType(int _object_type) {
  object_type = _object_type;
}

double ObjectInfo::getObjectWidth() const {
  return map_info.getObjectWidth();
}

void ObjectInfo::setObjectWidth(double object_width) {
  map_info.setObjectWidth(object_width);
}

double ObjectInfo::getObjectHeight() const {
  return map_info.getObjectHeight();
}

void ObjectInfo::setObjectHeight(double object_height) {
  map_info.setObjectHeight(object_height);
}

int ObjectInfo::getObjectSide() const {
  return map_info.getObjectSide();
}

void ObjectInfo::setObjectSide(double object_side) {
  map_info.setObjectWidth(object_side);
}

double ObjectInfo::getHitDistance() const {
  return map_info.getHitDistance();
}

void ObjectInfo::setHitDistance(double hit_distance) {
  map_info.setHitDistance(hit_distance);
}

double ObjectInfo::getHitGridPos() const {
  return map_info.getHitGridPos();
}

void ObjectInfo::setHitGridPos(double hit_grid_pos) {
  map_info.setHitGridPos(hit_grid_pos);
}

std::pair<int, int> ObjectInfo::getMapStartingPos() const {
  return map_info.getMapStartingPos();
}
void ObjectInfo::setMapStartingPos(std::pair<int, int> map_starting_pos) {
  map_info.setMapStartingPos(std::move(map_starting_pos));
}


