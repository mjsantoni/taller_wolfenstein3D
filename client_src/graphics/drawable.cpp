//
// Created by andy on 10/12/20.
//

#include <iostream>
#include "client/drawable.h"

Drawable::Drawable(int _object_type) : object_type(_object_type),
                                       sprite_animation_no(0) {
  if (object_type == ENEMY_DOG) {
    moving_sprites = std::vector<int>{1, 2, 4, 5, 6};
    shooting_sprite = std::vector<int>{0};
    dying_sprites = std::vector<int>{6, 8};
  }
}

Drawable::Drawable(int _object_type, int duration) :
    object_type(_object_type), duration_on_map(duration) {}

int Drawable::getObjectType() {
  return object_type;
}

std::pair<int, int> Drawable::getMapPosition() {
  return map_position;
}

int Drawable::getMapWidth() {
  return map_width;
}

std::string Drawable::getObjectName() {
  return object_name;
}

void Drawable::setMapWidth(int width) {
  map_width = width;
}

void Drawable::setMapPosition(int x_pos, int y_pos) {
  std::pair<int, int> new_position{x_pos, y_pos};
  map_position = new_position;
}

void Drawable::setMapPosition(std::pair<int, int> new_position) {
  map_position = new_position;
}

void Drawable::setObjectName(std::string name) {
  object_name = name;
}

int Drawable::getId() const {
  return id;
}

void Drawable::setId(int _id) {
  id = _id;
}

int Drawable::getSpriteAnimationNo() {
  return sprite_animation_no;
}

void Drawable::setSpriteAnimationNo(int _sprite_animation_no) {
  sprite_animation_no = _sprite_animation_no;
}

void Drawable::setObjectType(int _object_type) {
  object_type = _object_type;
}

void Drawable::reduceDuration() {
  --duration_on_map;
}

int Drawable::getDuration() {
  return duration_on_map;
}

double Drawable::getHitDistance() {
  return hit_distance;
}

void Drawable::setHitDistance(double _hit_distance) {
  hit_distance = _hit_distance;
}
