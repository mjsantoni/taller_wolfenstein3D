//
// Created by andy on 16/2/21.
//

#include "client/graphics/message_parameters.h"

MessageParameters::MessageParameters(SDL_Color _font_color, std::string _text,
                                     std::string _font_name, int _font_size) {
    font_color = _font_color;
    text = std::move(_text);
    font_name = std::move(_font_name);
    font_size = _font_size;
}

MessageParameters::MessageParameters(const std::string& _text) {
    font_color = SDL_Color{255, 255, 255};
    text = _text;
    font_name = "AnkeHand.ttf";
    font_size = 25;
}

MessageParameters::MessageParameters(const std::string& _text,
                                     const std::string& _font_name,
                                     int _font_size) {
    font_color = SDL_Color{255, 255, 255};
    text = _text;
    font_name = _font_name;
    font_size = _font_size;
}

const std::string &MessageParameters::getText() const {
    return text;
}

void MessageParameters::setText(const std::string& _text) {
    text = _text;
}

const std::string &MessageParameters::getFontName() const {
    return font_name;
}

void MessageParameters::setFontName(const std::string& _font_name) {
    font_name = _font_name;
}

const SDL_Color &MessageParameters::getFontColor() const {
    return font_color;
}

void MessageParameters::setFontColor(const SDL_Color& _font_color) {
    font_color = _font_color;
}

int MessageParameters::getFontSize() const {
    return font_size;
}

void MessageParameters::setFontSize(int _font_size) {
    font_size = _font_size;
}
