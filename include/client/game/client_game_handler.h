//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_GAME_HANDLER_H
#define TP_WOLFENSTEIN_CLIENT_GAME_HANDLER_H

#include <SDL.h>
#include "client/graphics/ray_caster.h"
#include "client/graphics/sdl_window.h"
#include "client/graphics/sdl_texture.h"
#include "client/sdl_exception.h"
#include "client_map.h"
#include "sdl_audio_player.h"
#include "client/graphics/game_screen.h"
#include "client/communication/client_parser.h"
#include "client_event_handler.h"
#include "event_generator.h"
#include "change_processor.h"
#include <vector>
#include <common/change.h>
#include <common/shared_queue.h>
#include <common/map_parser.h>
#include <common/config_parser.h>
#include <client/sounds/audio_manager.h>
#include "client_map_generator.h"
#include "client_player_initializer.h"
#include "off_game_change_processor.h"
#include "intro_handler.h"

class ClientGameHandler {
private:
    GameScreen screen;
    ClientMap map;
    ClientPlayer player = ClientPlayer("Player 1");
    AudioManager audio_manager;
    std::atomic<bool> running;
    EventGenerator event_generator;
    ClientParser client_parser;
    ClientEventHandler event_handler;
    OffGameChangeProcessor off_game_change_processor;
    ChangeProcessor change_processor;
    bool game_started;
    bool player_ready;
    IntroHandler intro_handler;
    ClientPlayerInitializer player_initializer;
    std::string map_path;
public:
    ClientGameHandler(SharedQueue<Change>& change_queue,
                      BlockingQueue<Event>& event_queue);
    void start();
    void killPlayer();
    void respawnPlayer();
    bool isRunning();
    void initializePlayer();
    void initializeMap();
};


#endif //TP_WOLFENSTEIN_CLIENT_GAME_HANDLER_H
