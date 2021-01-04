//
// Created by andy on 29/12/20.
//

#ifndef TP_WOLFENSTEIN_OBJECT_INFO_PROVIDER_H
#define TP_WOLFENSTEIN_OBJECT_INFO_PROVIDER_H


#include <vector>
#include "image_info.h"
#include "image_parser.h"

class ObjectInfoProvider {
private:
    std::vector<ImageInfo> image_info_vector;
    ImageParser image_parser;
public:
    ObjectInfoProvider();
    ImageInfo getObjectInfo(int object_type);
};


#endif //TP_WOLFENSTEIN_OBJECT_INFO_PROVIDER_H
