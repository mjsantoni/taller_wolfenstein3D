//
// Created by andy on 10/12/20.
//

#ifndef TP_WOLFENSTEIN_DRAWABLE_H
#define TP_WOLFENSTEIN_DRAWABLE_H

#include <utility>
#include <string>
#include <vector>
#include "client/graphics/images.h"

class Drawable {
 private:
  int object_type;
  std::string object_name;
  int sprite_animation_no;
  std::pair<int, int> map_position;
  int map_width;
  int id;
  int duration_on_map;
  double hit_distance;
 public:
  int getId() const;
  void setId(int id);
  explicit Drawable(int _object_type);
  Drawable(int _object_type, int _sprite_animation_no);
  int getObjectType();
  std::pair<int, int> getMapPosition();
  void setMapPosition(int x_pos, int y_pos);
  int getMapWidth();
  void setMapWidth(int width);
  std::string getObjectName();
  void setObjectName(std::string name);
  void setMapPosition(std::pair<int, int> new_position);
  std::vector<int> moving_sprites{0, 1, 3, 4, 7};
  std::vector<int> shooting_sprite = {6};
  std::vector<int> dying_sprites = {5, 8};
  int current_mov_sprite = 0;
  int current_sho_sprite = 0;
  int current_dying_sprite = 0;
  int getSpriteAnimationNo();
  void setSpriteAnimationNo(int _sprite_animation_no);
  void setObjectType(int _object_type);
  int getDuration();
  void reduceDuration();
  double getHitDistance();
  void setHitDistance(double _hit_distance);
};

#endif //TP_WOLFENSTEIN_DRAWABLE_H
