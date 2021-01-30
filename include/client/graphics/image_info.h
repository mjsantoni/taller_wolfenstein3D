//
// Created by andy on 10/12/20.
//

#ifndef TP_WOLFENSTEIN_IMAGE_INFO_H
#define TP_WOLFENSTEIN_IMAGE_INFO_H

#include <string>

class ImageInfo {
private:
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
private:
    int image_width;
    int image_height;
    std::string object_name;
    std::string image_path;
    int sprite_animation_no = 0;
    int sprite_rows;
    int sprite_cols;
    int sprite_h_padding;
    int sprite_v_padding;
    bool is_sprite;
};


#endif //TP_WOLFENSTEIN_IMAGE_INFO_H
