//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_GAME_H
#define TP_WOLFENSTEIN_CLIENT_GAME_H

#include "map_mock.h"
#include <SDL.h>
#include "ray_caster.h"
#include "sdl_window.h"
#include "sdl_texture.h"
#include "sdl_exception.h"

#include "event_handler_mock.h"
#include "client_map.h"
#include "sdl_audio_player.h"
#include "game_screen.h"
#include "client_parser.h"
#include <vector>

class ClientGame {
public:
    ClientGame(int map_width, int map_height, MapMock real_map,
               ClientMap& _map);
    void start();
private:
    bool running;
    SdlAudioPlayer audio_player;
    ClientMap map;
    EventHandlerMock event_handler;
    ObjectInfoProvider info_provider;
    GameScreen screen;
    ClientParser client_parser;
    void displayIntro();
};


#endif //TP_WOLFENSTEIN_CLIENT_GAME_H
