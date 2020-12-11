//
// Created by andy on 10/12/20.
//

#ifndef TP_WOLFENSTEIN_IMAGE_PARSER_H
#define TP_WOLFENSTEIN_IMAGE_PARSER_H


#include <vector>
#include "image_info.h"

class ImageParser {
private:
    ImageInfo processLine(std::string line);
public:
    void fillImageVector(std::vector<ImageInfo>& vector);
};


#endif //TP_WOLFENSTEIN_IMAGE_PARSER_H
