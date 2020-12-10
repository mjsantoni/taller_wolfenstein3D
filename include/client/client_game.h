//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_GAME_H
#define TP_WOLFENSTEIN_CLIENT_GAME_H

#include <SDL.h>
#include "client/sdl_window.h"
#include "client/sdl_texture.h"
#include "client/sdl_exception.h"
#include "client_map.h"
#include "sdl_audio_player.h"
#include <vector>

class ClientGame {
public:
    ClientGame(int width, int height, int map_width, int map_height);
    void start(std::vector<std::pair<int,int>> walls);
private:
    bool running;
    SdlWindow window;
    SdlAudioPlayer audio_player;
    ClientMap map;

    void displayIntro();

};


#endif //TP_WOLFENSTEIN_CLIENT_GAME_H
