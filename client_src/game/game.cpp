//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include <SDL_timer.h>
#include "client/game.h"

Game::Game(int width, int height, MapMock real_map) :
                            running(true), event_handler(real_map),
                            screen(width, height, info_provider, map) {}

void Game::start() {
    displayIntro();
    map = client_parser.parseInfoFromServer();
    ClientPlayer player("Player1");
    int x = 235;
    int y = 329;
    event_handler.putPlayerAt(player.getPlayerName(), std::pair<int, int>(x,y));
    map.putPlayerAt(player.getPlayerName(), std::pair<int, int>(x, y));
    screen.render();
    while (running) {
        bool must_render = false;
        SDL_Event event;
        SDL_PollEvent(&event);
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
            screen.render();
    }
}

void Game::displayIntro() {
    audio_player.playSong("../client_src/resources/music.wav");
    screen.displayIntro();
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
