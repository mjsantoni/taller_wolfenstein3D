//
// Created by andy on 10/2/21.
//

#ifndef TP_WOLFENSTEIN_INTRO_HANDLER_H
#define TP_WOLFENSTEIN_INTRO_HANDLER_H

#include <client/sounds/audio_manager.h>
#include <client/graphics/game_screen.h>
#include "off_game_change_processor.h"
#include "off_game_event_handler.h"
#include <common/map_parser.h>
#include <client/game/client_map_generator.h>

class IntroHandler {
private:
    GameScreen& screen;
    ClientMap& map;
    AudioManager audio_manager;
    OffGameChangeProcessor change_processor;
    OffGameEventHandler event_handler;
    bool& player_ready;
    bool& game_started;
    std::string& map_path;
public:
    IntroHandler(GameScreen &_screen, ClientMap& _map, std::string &_map_path,
                 OffGameChangeProcessor &_change_processor, bool& _game_started,
                 bool& _player_ready);
    void setMapPath(int chosen_map);
    void displayLoadingScreen();
    void displayLevelSelectionMenu();
    int displayMatchModeMenu();
    void displayIntro();
    void displayMenus();

    void initializeMap();
};


#endif //TP_WOLFENSTEIN_INTRO_HANDLER_H
