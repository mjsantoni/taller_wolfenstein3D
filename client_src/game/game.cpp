//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include <SDL_timer.h>
#include "client/game.h"
#include "client/ray_caster.h"
#include <SDL_mixer.h>

Game::Game(int width, int height, ClientMap _map, MapMock real_map) :
window(width, height), running(true), map(_map), event_handler(real_map) {
}

void Game::start() {
    displayIntro();
    ClientPlayer player("Player1");
    int x = 192;
    int y = 128;
    event_handler.putPlayerAt(player.getPlayerName(), std::pair<int, int>(x,y));
    map.putPlayerAt(player.getPlayerName(), std::pair<int, int>(x, y));
    RayCaster ray_caster(window, map);
    ray_caster.render3DScreen(x, y, player.getDirection());
    while (running) {
        bool must_render = false;
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                event_handler.handleEvent(event, player, running, x, y);
                must_render = true;
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_QUIT:
                puts("Saliendo");
                return;
        }
        if (must_render)
            ray_caster.render3DScreen(x, y, player.getDirection());
    }
}

void Game::displayIntro() {
    SdlTexture intro_tex("../client_src/resources/intro.jpg");
    window.displayFullImage(intro_tex);
    window.render();
    audio_player.playSong("../client_src/resources/music.wav");
    bool run_intro = true;
    while (run_intro) {
        SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                run_intro = false;
                break;
        }
    }
    audio_player.stopSong();
}
