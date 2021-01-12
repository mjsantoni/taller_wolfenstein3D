//
// Created by andy on 10/12/20.
//

#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>
#include <client/file_exception.h>
#include "client/image_parser.h"

void ImageParser::fillImageVector(std::vector<ImageInfo>& vector) {
    std::ifstream infile("../client_src/resources/objects_info.txt");
    if (!infile)
        throw FileException("Archivo de imagenes no encontrado");
    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty())
            return;
        ImageInfo image_info = processLine(line);
        vector.push_back(std::move(image_info));
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

void getSpriteInfo(ImageInfo& image_info,
                   std::string dimensions,
                   std::string padding) {
    image_info.sprite_rows = stoi(dimensions.substr(dimensions.find(':')
            +1, dimensions.find('x')));
    image_info.sprite_cols = stoi(dimensions.substr(dimensions.find('x')
            + 1));
    image_info.sprite_v_padding = stoi(padding.substr(padding.find(':')
                                                    +1, padding.find('x')));
    image_info.sprite_h_padding = stoi(padding.substr(padding.find('x')
                                                    + 1));
}

void cleanVector(std::vector<std::string> vector) {
    for (int i = 0; i < vector.size(); ++i) {
        if (vector[i][0] == ' ')
            vector.erase(vector.begin()+i);
    }
}

ImageInfo ImageParser::processLine(std::string line) {
    ImageInfo image_info;
    std::vector<std::string> aux;
    split(line, aux);
    image_info.image_path = getCorrectValue(aux[0]);
    image_info.object_width = stof(getCorrectValue(aux[1]));
    image_info.object_height = stof(getCorrectValue(aux[2]));
    image_info.image_width = stoi(getCorrectValue(aux[3]));
    image_info.image_height = stoi(getCorrectValue(aux[4]));
    image_info.object_name = getStringValue(aux[5]);
    image_info.is_sprite = stoi(getCorrectValue(aux[6]));
    if (image_info.is_sprite)
        getSpriteInfo(image_info, aux[7], aux[8]);
    return image_info;
}


