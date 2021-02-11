//
// Created by andy on 10/2/21.
//

#ifndef TP_WOLFENSTEIN_OFF_GAME_HANDLER_H
#define TP_WOLFENSTEIN_OFF_GAME_HANDLER_H

#include <client/sounds/audio_manager.h>
#include <client/graphics/game_screen.h>
#include "off_game_change_processor.h"
#include "off_game_event_handler.h"
#include "event_generator.h"
#include "off_game_event_generator.h"
#include <common/map_parser.h>
#include <client/game/client_map_generator.h>

class OffGameHandler {
private:
    GameScreen& screen;
    ClientMap& map;
    AudioManager audio_manager;
    OffGameChangeProcessor change_processor;
    OffGameEventHandler event_handler;
    bool player_ready = false;
    bool game_started = false;
    std::string map_path;
    OffGameEventGenerator event_generator;
public:
    OffGameHandler(GameScreen &_screen, ClientPlayer& player, ClientMap& _map,
                   SharedQueue<Change>& change_queue,
                   BlockingQueue<Event>& event_queue);
    void setMapPath(int chosen_map);
    void displayLoadingScreen();
    void displayLevelSelectionMenu();
    int displayMatchModeMenu();
    void displayIntro();
    void displayMenus();

    void initializeMap();
};


#endif //TP_WOLFENSTEIN_OFF_GAME_HANDLER_H
