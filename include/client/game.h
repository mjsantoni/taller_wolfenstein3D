//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_GAME_H
#define TP_WOLFENSTEIN_GAME_H

#include <SDL.h>
#include "client/sdl_window.h"
#include "client/sdl_texture.h"
#include "client/sdl_exception.h"
#include "map.h"
#include "event_handler.h"
#include "sdl_audio_player.h"
#include <vector>

class Game {
public:
    Game(int width, int height, int map_width, int map_height);
    void start(std::vector<std::pair<int,int>> walls);
private:
    bool running;
    EventHandler event_handler;
    SdlWindow window;
    SdlAudioPlayer audio_player;
    Map map;

    void displayIntro();

};


#endif //TP_WOLFENSTEIN_GAME_H
