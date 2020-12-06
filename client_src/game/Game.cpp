//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include <SDL_timer.h>
#include "client/Game.h"
#include "client/RayCaster.h"
#include <SDL_mixer.h>

Game::Game(int width, int height) : window(width, height), running(true), map(window, 8, 10) {
}

void Game::start() {
    displayIntro();
    map.initialize();
    Player player("Player1");
    int x = 200;
    int y = 170;
    map.putPlayerAt(player.getPlayerName(), std::pair<int, int>(x, y));
    //map.update(player, x, y);
    RayCaster ray_caster(window, map);
    event_handler.getMousePosition();
    ray_caster.render3DScreen(x, y, player.getDirection());
    bool must_render = false;
    while (running) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                event_handler.handleEvent(event, player, map, running, x, y);
                must_render = true;
                break;
            case SDL_MOUSEMOTION:
                event_handler.handleMouseEvent(event, player, window);
                must_render = true;
                break;
            case SDL_QUIT:
                puts("Saliendo");
                return;
        }
        if (must_render)
            ray_caster.render3DScreen(x, y, player.getDirection());
    }
    /*while (running) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN:
                event_handler.handleEvent(event, player, map, running, x, y);
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                puts("Se minimiza la ventana");
                SDL_Delay(3000);
                window.restore();
            case SDL_QUIT:
                return;
        }
    }
    */
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
