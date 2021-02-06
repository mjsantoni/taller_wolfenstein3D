//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_GAME_HANDLER_H
#define TP_WOLFENSTEIN_CLIENT_GAME_HANDLER_H

#include <SDL.h>
#include "event_handler_mock.h"
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

class ClientGameHandler {
public:
    ClientGameHandler(int map_width, int map_height, MapMock& real_map,
                      ClientMap& _map, SharedQueue<Change>& change_queue,
                      BlockingQueue<Event>& event_queue);
    void start();
    void killPlayer();
    void respawnPlayer();
    bool isRunning();
private:
    ClientPlayer player = ClientPlayer("Player 1");
    std::atomic<bool> running;
    SdlAudioPlayer audio_player;
    ClientMap map;
    EventHandlerMock event_handler_mockup;
    EventGenerator event_generator;
    ObjectInfoProvider info_provider;
    GameScreen screen;
    ClientParser client_parser;
    ClientEventHandler client_event_handler = ClientEventHandler(player,screen);
    ChangeProcessor change_processor;
    int game_level = 0;
    void displayIntro();
    int displayMatchModeMenu();
    void displayLevelSelectionMenu();
};


#endif //TP_WOLFENSTEIN_CLIENT_GAME_HANDLER_H
