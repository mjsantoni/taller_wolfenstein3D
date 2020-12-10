//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include <SDL_timer.h>
#include "client/client_game.h"
#include "client/ray_caster.h"
#include <SDL_mixer.h>

ClientGame::ClientGame(int width, int height, int map_width, int map_height) :
window(width, height), running(true), map(window, map_width, map_height) {
}

void ClientGame::start(std::vector<std::pair<int,int>> walls) {
    displayIntro();
    map.initialize();
    map.addWalls(walls);
    ClientPlayer player("Player1");
    int x = 200;
    int y = 170;
    map.putPlayerAt(player.getPlayerName(), std::pair<int, int>(x, y));
    //map.update(player, x, y);
    RayCaster ray_caster(window, map);
    ray_caster.render3DScreen(x, y, player.getDirection());
    bool must_render = false;
    while (running) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                must_render = true;
                break;
            case SDL_MOUSEMOTION:
                must_render = false;
                break;
            case SDL_QUIT:
                puts("Saliendo");
                return;
        }
        if (must_render)
            ray_caster.render3DScreen(x, y, player.getDirection());
    }
}

void ClientGame::displayIntro() {
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
