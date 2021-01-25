//
// Created by andy on 10/12/20.
//

#ifndef TP_WOLFENSTEIN_IMAGE_PARSER_H
#define TP_WOLFENSTEIN_IMAGE_PARSER_H


#include <vector>
#include "image_info.h"
#include "object_info.h"
#include "file_exception.h"

class ImageParser {
private:
    ObjectInfo processLine(std::string line);
public:
    void fillImageVector(std::vector<ObjectInfo>& vector);
};


#endif //TP_WOLFENSTEIN_IMAGE_PARSER_H
