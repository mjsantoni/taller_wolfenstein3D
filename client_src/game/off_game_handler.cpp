//
// Created by andy on 10/2/21.
//

#include <SDL_events.h>
#include <SDL_timer.h>
#include "client/game/off_game_handler.h"

#define MAPS_PATH "../maps/ww"

OffGameHandler::OffGameHandler(GameScreen& _screen,
                               ClientPlayer& player,
                               ClientMap& _map,
                               SharedQueue<Change>& change_queue,
                               BlockingQueue<Event>& event_queue) :
                           screen(_screen),
                           map(_map),
                           change_processor(_map, player, change_queue,
                                            game_started, player_ready),
                           event_generator(event_queue, player) {
}

void OffGameHandler::displayMenus(const std::string &map_name) {
    //event_handler.defineKeyScreenAreas(screen.getKeyScreenAreas());
    audio_manager.playSong();
    //displayIntro();
    //std::cout << "Se inicia el juego" << std::endl;
    //int game_mode = displayMatchModeMenu();
    //if (game_mode != 1)
        //return;
    //displayLevelSelectionMenu();
    initializeMap(map_name);
    displayLoadingScreen();
    //sleep(1);
    audio_manager.stopSong();
}

void OffGameHandler::displayIntro() {
    screen.displayIntro();
    while (true) {
        //SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
            break;
    }
}

int OffGameHandler::displayMatchModeMenu() {
    screen.displayMatchModeMenu();
    int ret_code = 0;
    while (true) {
        //SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        ret_code = event_handler.handleMatchModeScreenEvent(event);
        if (ret_code != 0)
            break;
    }
    return ret_code;
}

void OffGameHandler::displayLevelSelectionMenu() {
    screen.displayLevelSelectionMenu();
    while (true) {
        //SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        int chosen_map = event_handler.handleLevelSelectionEvent(event);
        if (chosen_map != 0) {
            break;
        }
    }
}

void OffGameHandler::displayLoadingScreen() {
    screen.displayLoadingScreen(true);
    while (!player_ready)
        change_processor.processOffGameChanges();
    while (true) {
        //SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        bool player_pressed_p = event_handler.handleLoadingScreenEvent(event);
        if (player_pressed_p) {
            event_generator.generateReadyEvent();
            break;
        }
    }
    while (!game_started) {
        usleep(30000);
        screen.displayLoadingScreen(false);
        change_processor.processOffGameChanges();
    }
    std::cout << "TERMINA LA INTRO\n";
}

void OffGameHandler::initializeMap(const std::string &map_name) {
    std::string map_path = MAPS_PATH + map_name;
    MapParser map_parser(map_path);
    ClientMapGenerator::create(map, map_parser);
}

