//
// Created by andy on 10/12/20.
//

#ifndef TP_WOLFENSTEIN_IMAGE_INFO_H
#define TP_WOLFENSTEIN_IMAGE_INFO_H

#include <string>

class ImageInfo {
private:
public:
    double object_width;
    double object_height;
    int image_width;
    int image_height;
    std::string object_name;
    std::string image_path;
    int sprite_animation_no;

};


#endif //TP_WOLFENSTEIN_IMAGE_INFO_H
