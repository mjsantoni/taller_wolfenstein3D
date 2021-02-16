//
// Created by andy on 16/2/21.
//

#ifndef TP_WOLFENSTEIN_MESSAGE_PARAMETERS_H
#define TP_WOLFENSTEIN_MESSAGE_PARAMETERS_H

#include <string>
#include <SDL_pixels.h>

class MessageParameters {
private:
    std::string text;
    std::string font_name;
    SDL_Color font_color;
    int font_size;
public:
    MessageParameters(const std::string &_text);
    MessageParameters(const std::string &_text, const std::string &_font_name,
                      int _font_size);
    MessageParameters(SDL_Color _font_color, std::string _text,
                      std::string _font_name, int _font_size);
    const std::string &getText() const;
    void setText(const std::string &text);
    const std::string &getFontName() const;
    void setFontName(const std::string &fontName);
    const SDL_Color &getFontColor() const;
    void setFontColor(const SDL_Color &fontColor);
    int getFontSize() const;
    void setFontSize(int fontSize);
};


#endif //TP_WOLFENSTEIN_MESSAGE_PARAMETERS_H
