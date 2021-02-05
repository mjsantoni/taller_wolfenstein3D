//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include <SDL_timer.h>
#include "client/game/client_game_handler.h"

ClientGameHandler::ClientGameHandler(int width, int height, MapMock real_map,
                                     ClientMap& _map, ServerUpdater& _server_updater) :
        running(true), event_handler_mockup(real_map), map(_map),
        screen(width, height, info_provider, _map),
        event_generator(player, client_event_handler,
                                            _server_updater){
    client_event_handler.defineKeyScreenAreas(screen.getKeyScreenAreas());
}

void ClientGameHandler::start() {
    displayIntro();
    int game_mode = displayMatchModeMenu();
    if (game_mode != 1)
        return;
    displayLevelSelectionMenu();
    int x = 235;
    int y = 329;
    event_handler_mockup.putPlayerAt(player.getPlayerName(), std::pair<int, int>(x, y));
    map.putPlayerAt(player.getPlayerName(), std::pair<int, int>(x, y));
    screen.render(x, y, player);
    while (running) {
        bool must_render = false;
        SDL_Event event;
        SDL_PollEvent(&event);
        event_generator.generateInGameEvent(event);
        switch(event.type) {
            case SDL_KEYDOWN:
                event_handler_mockup.handleEvent(event, player, running, x, y);
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

void ClientGameHandler::displayIntro() {
    audio_player.playSong("../client_src/resources/music.wav");
    screen.displayIntro();
    bool run_intro = true;
    while (run_intro) {
        SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        event_generator.generateInGameEvent(event);
        switch(event.type) {
            case SDL_KEYDOWN:
                run_intro = false;
                break;
        }
    }
    audio_player.stopSong();
}

int ClientGameHandler::displayMatchModeMenu() {
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

void ClientGameHandler::displayLevelSelectionMenu() {
    audio_player.playSong("../client_src/resources/music.wav");
    screen.displayLevelSelectionMenu();
    while (true) {
        SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        game_level = client_event_handler.handleLevelSelectionEvent(event);
        if (game_level != 0)
            break;
    }
    audio_player.stopSong();
}


void ClientGameHandler::killPlayer() {
    //event_generator.stop();
    screen.renderDeadScreen();
}

void ClientGameHandler::respawnPlayer() {
    player.respawn();
    screen.renderRespawnScreen();
}


