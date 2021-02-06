//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include <SDL_timer.h>
#include "client/game/client_game_handler.h"
#include <client/communication/server_updater.h>


ClientGameHandler::ClientGameHandler(int width,
                                     int height,
                                     MapMock& real_map,
                                     ClientMap& _map,
                                     SharedQueue<Change>& change_queue,
                                     BlockingQueue<Event>& event_queue) :
        running(true), event_handler_mockup(real_map), map(_map),
        screen(width, height, info_provider, _map),
        event_generator(player, client_event_handler, event_queue),
        change_processor(_map, player, screen, change_queue) {
    client_event_handler.defineKeyScreenAreas(screen.getKeyScreenAreas());
}

void ClientGameHandler::start() {
    displayIntro();
    std::cout << "Se inicia el juego" << std::endl;
    int game_mode = displayMatchModeMenu();
    if (game_mode != 1)
        return;
    displayLevelSelectionMenu();
    int x = 235;
    int y = 329;
    event_handler_mockup.putPlayerAt(player.getPlayerName(), std::pair<int, int>(x, y)); // mapa del "server"
    map.putPlayerAt(player.getPlayerName(), std::pair<int, int>(x, y)); // mapa del cliente
    screen.render(x, y, player);
    change_processor.start();
    std::cout << "Se inicia la partida" << std::endl;
    SDL_Event event;
    while (running) {
        if (SDL_PollEvent(&event) == 0) continue;
        switch(event.type) {
            case SDL_KEYDOWN: {
                event_generator.generateInGameEvent(event);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
                event_generator.generateInGameEvent(event);
                break;
            case SDL_QUIT:
                puts("Saliendo");
                return;
            default:
                break;
        }
        //sleep(10);
    }
    std::cout << "Frena change processor" << std::endl;
    change_processor.stop();
    change_processor.join();
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

bool ClientGameHandler::isRunning() {
    return running;
}

