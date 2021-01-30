//
// Created by andy on 29/12/20.
//

#ifndef TP_WOLFENSTEIN_OBJECT_INFO_PROVIDER_H
#define TP_WOLFENSTEIN_OBJECT_INFO_PROVIDER_H


#include <vector>
#include "client/graphics/image_info.h"
#include "client/graphics/image_parser.h"
#include "object_info.h"

class ObjectInfoProvider {
private:
    std::vector<ObjectInfo> image_info_vector;
    ImageParser image_parser;
public:
    ObjectInfoProvider();
    ObjectInfo getObjectInfo(int object_type);
};


#endif //TP_WOLFENSTEIN_OBJECT_INFO_PROVIDER_H
