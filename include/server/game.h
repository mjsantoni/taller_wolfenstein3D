//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_GAME_H
#define TP_WOLFENSTEIN_GAME_H


#include "client/client_map.h"
#include "event_handler.h"
#include "client/sdl_audio_player.h"

class Game {
public:
    Game(int width, int height);
    void start();
private:
    bool running;
    EventHandler event_handler;
    SdlWindow window;
    SdlAudioPlayer audio_player;
    Map map;

    void displayIntro();

};


#endif //TP_WOLFENSTEIN_GAME_H
