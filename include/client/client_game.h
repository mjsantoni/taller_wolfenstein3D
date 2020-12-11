//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_GAME_H
#define TP_WOLFENSTEIN_CLIENT_GAME_H

#include <SDL.h>
#include "client/sdl_window.h"
#include "client/sdl_texture.h"
#include "client/sdl_exception.h"
#include "client/client_event_handler.h"
#include "client_map.h"
#include "sdl_audio_player.h"
#include <vector>

class ClientGame {
public:
    ClientGame(int map_width, int map_height, ClientMap _map, Map real_map);
    void start();
private:
    bool running;
    SdlWindow window;
    SdlAudioPlayer audio_player;
    ClientMap map;
    ClientEventHandler event_handler;

    void displayIntro();

};


#endif //TP_WOLFENSTEIN_CLIENT_GAME_H
