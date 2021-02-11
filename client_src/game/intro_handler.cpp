//
// Created by andy on 10/2/21.
//

#include <SDL_events.h>
#include <SDL_timer.h>
#include "client/game/intro_handler.h"

IntroHandler::IntroHandler(GameScreen& _screen,
                           ClientMap& _map,
                           std::string& _map_path,
                           OffGameChangeProcessor& _change_processor,
                           bool& _game_started,
                           bool& _player_ready,
                           EventGenerator& _event_generator) :
                           screen(_screen),
                           map(_map),
                           map_path(_map_path),
                           change_processor(_change_processor),
                           game_started(_game_started),
                           player_ready(_player_ready),
                           event_generator(_event_generator) {
}

void IntroHandler::displayMenus() {
    event_handler.defineKeyScreenAreas(screen.getKeyScreenAreas());
    audio_manager.playSong();
    displayIntro();
    std::cout << "Se inicia el juego" << std::endl;
    int game_mode = displayMatchModeMenu();
    if (game_mode != 1)
        return;
    displayLevelSelectionMenu();
    initializeMap();
    displayLoadingScreen();
    sleep(1);
    audio_manager.stopSong();
}

void IntroHandler::displayIntro() {
    screen.displayIntro();
    while (true) {
        SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
            break;
    }
}

int IntroHandler::displayMatchModeMenu() {
    screen.displayMatchModeMenu();
    int ret_code = 0;
    while (true) {
        SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        ret_code = event_handler.handleMatchModeScreenEvent(event);
        if (ret_code != 0)
            break;
    }
    return ret_code;
}

void IntroHandler::displayLevelSelectionMenu() {
    screen.displayLevelSelectionMenu();
    while (true) {
        SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        int chosen_map = event_handler.handleLevelSelectionEvent(event);
        if (chosen_map != 0) {
            setMapPath(chosen_map);
            break;
        }
    }
}

void IntroHandler::displayLoadingScreen() {
    screen.displayLoadingScreen(true);
    while (!player_ready)
        change_processor.processOffGameChanges();
    while (true) {
        SDL_Delay(1);
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

void IntroHandler::setMapPath(int chosen_map) {
    map_path =  "../map.yaml";
}

void IntroHandler::initializeMap() {
    MapParser map_parser(map_path);
    ClientMapGenerator::create(map, map_parser);
    //player.setMapPosition(std::pair<int, int>{128, 128});
    //map.putPlayerAt(std::pair<int, int>(128, 128));
}

