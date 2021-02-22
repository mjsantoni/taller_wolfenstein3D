//
// Created by andy on 10/12/20.
//

#ifndef TP_WOLFENSTEIN_IMAGE_PARSER_H
#define TP_WOLFENSTEIN_IMAGE_PARSER_H

#include <vector>
#include "image_info.h"
#include "client/object_info.h"
#include "client/file_exception.h"
#include "client_routes.h"

class ImageParser {
 private:
  static void processLine(std::vector<ObjectInfo>& vector,
                          const std::string& line, int object_type);
    static std::string getCorrectDoubleValue(const std::string& complete_value);
    static std::string parseFormat(std::string value);
    static std::string getCorrectValue(const std::string& complete_value);
    static void getSpriteInfo(ObjectInfo &object_info,
                              const std::string &dimensions,
                              const std::string &padding);
    static void addFakeObject(std::vector<ObjectInfo> &vector);
    static std::string getStringValue(const std::string& complete_value);
 public:
  void fillImageVector(std::vector<ObjectInfo>& vector);
};

#endif //TP_WOLFENSTEIN_IMAGE_PARSER_H
