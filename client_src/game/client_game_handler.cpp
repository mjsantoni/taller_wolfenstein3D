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
                                     SharedQueue<Change>& change_queue,
                                     BlockingQueue<Event>& event_queue) :
        running(true),
        screen(width, height, info_provider, map, player),
        event_generator(player, client_event_handler, event_queue),
        change_processor(map, player, screen, change_queue) {
    client_event_handler.defineKeyScreenAreas(screen.getKeyScreenAreas());
}

void ClientGameHandler::start() {
    displayIntro();
    std::cout << "Se inicia el juego" << std::endl;
    int game_mode = displayMatchModeMenu();
    if (game_mode != 1)
        return;
    displayLevelSelectionMenu();
    MapParser map_parser(map_path);
    ClientMapGenerator::create(map, map_parser);
    player.setMapPosition(std::pair<int, int>{128, 128});
    map.putPlayerAt(std::pair<int, int>(128, 128)); // mapa del cliente
    screen.render();
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

void ClientGameHandler::setMapPath(int chosen_map) {
    map_path =  "../map.yaml";
}

void ClientGameHandler::displayLevelSelectionMenu() {
    audio_player.playSong("../client_src/resources/music.wav");
    screen.displayLevelSelectionMenu();
    while (true) {
        SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        int chosen_map = client_event_handler.handleLevelSelectionEvent(event);
        if (chosen_map != 0) {
            setMapPath(chosen_map);
            break;
        }
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

