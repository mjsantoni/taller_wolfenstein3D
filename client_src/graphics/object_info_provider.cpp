//
// Created by andy on 29/12/20.
//

#include "client/object_info_provider.h"

ObjectInfoProvider::ObjectInfoProvider() {
  image_parser.fillImageVector(image_info_vector);
}

ObjectInfo ObjectInfoProvider::getObjectInfo(int object_type) {
  return image_info_vector[object_type];
}


