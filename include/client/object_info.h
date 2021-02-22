//
// Created by andy on 22/1/21.
//

#ifndef TP_WOLFENSTEIN_OBJECT_INFO_H
#define TP_WOLFENSTEIN_OBJECT_INFO_H

#include "client/graphics/image_info.h"
#include "map_info.h"

class ObjectInfo {
 private:
  std::string object_name;
  int object_type;
 public:
  int getObjectType() const;
  void setObjectType(int objectType);

 private:
  ImageInfo image_info;
  MapInfo map_info;

 public:
  int getImageWidth() const;
  void setImageWidth(int imageWidth);
  int getImageHeight() const;
  void setImageHeight(int imageHeight);
  std::string getObjectName() const;
  void setObjectName(std::string objectName);
  std::string getImagePath() const;
  void setImagePath(std::string imagePath);
  int getSpriteAnimationNo() const;
  void setSpriteAnimationNo(int spriteAnimationNo);
  int getSpriteRows() const;
  void setSpriteRows(int spriteRows);
  int getSpriteCols() const;
  void setSpriteCols(int spriteCols);
  int getSpriteHPadding() const;
  void setSpriteHPadding(int spriteHPadding);
  int getSpriteVPadding() const;
  void setSpriteVPadding(int spriteVPadding);
  bool isSprite() const;
  void setIsSprite(bool isSprite);
  double getObjectWidth() const;
  void setObjectWidth(double object_width);
  double getObjectHeight() const;
  void setObjectHeight(double _object_width);
  int getObjectSide() const;
  void setObjectSide(double objectSide);
  double getHitDistance() const;
  void setHitDistance(double hitDistance);
  double getHitGridPos() const;
  void setHitGridPos(double hitGridPos);
  std::pair<int, int> getMapStartingPos() const;
  void setMapStartingPos(std::pair<int, int> mapStartingPos);
};

#endif //TP_WOLFENSTEIN_OBJECT_INFO_H
