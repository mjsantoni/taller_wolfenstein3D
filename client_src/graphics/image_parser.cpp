//
// Created by andy on 10/12/20.
//

#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include "client/image_parser.h"

void ImageParser::fillImageVector(std::vector<ObjectInfo>& vector) {
    std::ifstream infile("../client_src/resources/objects_info.txt");
    if (!infile)
        throw FileException("Archivo de imagenes no encontrado");
    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty())
            return;
        ObjectInfo object_info = processLine(line);
        vector.push_back(std::move(object_info));
    }
}

template <class Container>
void split(const std::string& str, Container& cont) {
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter(cont));
}

std::string getCorrectValue(std::string complete_value) {
    std::string aux = complete_value.substr(complete_value.find(':')+1);
    if (aux[aux.length()-1] == ',')
        return aux.substr(0, aux.length()-1);
    return aux.substr(0, aux.length());
}

std::string getStringValue(std::string complete_value) {
    std::string aux = complete_value.substr(complete_value.find(':')+1);
    return aux.substr(0, aux.length()-1);
}

void getSpriteInfo(ObjectInfo& object_info,
                   std::string dimensions,
                   std::string padding) {
    object_info.setSpriteRows(stoi(dimensions.substr(dimensions.find(':')
            +1, dimensions.find('x'))));
    object_info.setSpriteCols(stoi(dimensions.substr(dimensions.find('x')
            + 1)));
    object_info.setSpriteVPadding(stoi(padding.substr(padding.find(':')
            +1, padding.find('x'))));
    object_info.setSpriteHPadding(stoi(padding.substr(padding.find('x')
            + 1)));
}

void cleanVector(std::vector<std::string> vector) {
    for (int i = 0; i < vector.size(); ++i) {
        if (vector[i][0] == ' ')
            vector.erase(vector.begin()+i);
    }
}

ObjectInfo ImageParser::processLine(std::string line) {
    ObjectInfo object_info;
    std::vector<std::string> aux;
    split(line, aux);
    object_info.setImagePath(getCorrectValue(aux[0]));
    object_info.setImageWidth(stoi(getCorrectValue(aux[3])));
    object_info.setImageHeight(stoi(getCorrectValue(aux[4])));
    object_info.setObjectName(getStringValue(aux[5]));
    object_info.setIsSprite(stoi(getCorrectValue(aux[6])));
    if (object_info.isSprite())
        getSpriteInfo(object_info, aux[7], aux[8]);
    object_info.setObjectWidth(stof(getCorrectValue(aux[1])));
    return object_info;
}


