//
// Created by andy on 26/11/20.
//

#ifndef TP_WOLFENSTEIN_SDL_TEXTURE_H
#define TP_WOLFENSTEIN_SDL_TEXTURE_H

#include <string>
#include <SDL_render.h>
#include "area.h"
#include "client/sdl_exception.h"
#include "sdl_window.h"
#include <client/object_info.h>

class SdlTexture {
private:
    int width = 0;
    int height = 0;
    SDL_Texture* loadTexture(const std::string& file_name);
protected:
    std::string file_name;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
 public:
  SdlTexture(SdlTexture&) = delete;
  SdlTexture(SdlTexture&&) noexcept;
  SdlTexture();
  SdlTexture(SdlWindow& window, const std::string& _file_name);
  ~SdlTexture();
  Area getTextureArea();
  void operator=(const SdlTexture&) = delete;
  SdlTexture& operator=(SdlTexture&&) noexcept;
  void render(Area& src, Area& dest);
  void render(Area& dest);
  void render(Area &dest, int image_x_pos);
};

#endif //TP_WOLFENSTEIN_SDL_TEXTURE_H
