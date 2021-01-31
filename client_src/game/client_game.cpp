//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include <SDL_timer.h>
#include "client/game/client_game.h"

ClientGame::ClientGame(int width, int height, MapMock real_map,
                       ClientMap& _map) :
                            running(true), event_handler(real_map), map(_map),
                            screen(width, height, info_provider, _map) {
    client_event_handler.defineKeyScreenAreas(screen.getKeyScreenAreas());
}

void ClientGame::start() {
    displayIntro();
    int game_mode = displayMatchModeMenu();
    if (game_mode != 1)
        return;
    int x = 235;
    int y = 329;
    event_handler.putPlayerAt(player.getPlayerName(), std::pair<int, int>(x,y));
    map.putPlayerAt(player.getPlayerName(), std::pair<int, int>(x, y));
    screen.render(x, y, player);
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
            screen.render(x, y, player);
    }
}

void ClientGame::displayIntro() {
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

int ClientGame::displayMatchModeMenu() {
    audio_player.playSong("../client_src/resources/music.wav");
    screen.displayMatchModeMenu();
    int ret_code = 0;
    while (true) {
        SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        ret_code = client_event_handler.handleMatchModeScreenEvent(event);
        if (ret_code != 0)
            break;
    }
    audio_player.stopSong();
    return ret_code;
}

void ClientGame::killPlayer() {
    //event_generator.stop();
    screen.renderDeadScreen();
}

void ClientGame::respawnPlayer() {
    player.respawn();
    screen.renderRespawnScreen();
}
