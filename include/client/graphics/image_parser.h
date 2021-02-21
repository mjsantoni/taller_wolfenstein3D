//
// Created by andy on 10/12/20.
//

#ifndef TP_WOLFENSTEIN_IMAGE_PARSER_H
#define TP_WOLFENSTEIN_IMAGE_PARSER_H

#include <vector>
#include "image_info.h"
#include "client/object_info.h"
#include "client/file_exception.h"
#include "../../../client_src/client_routes.h"

class ImageParser {
private:
    void processLine(std::vector<ObjectInfo>& vector, std::string line,
                           int object_type);
public:
    void fillImageVector(std::vector<ObjectInfo>& vector);
};


#endif //TP_WOLFENSTEIN_IMAGE_PARSER_H
