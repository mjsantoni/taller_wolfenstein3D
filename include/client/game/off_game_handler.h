//
// Created by andy on 10/2/21.
//

#ifndef TP_WOLFENSTEIN_OFF_GAME_HANDLER_H
#define TP_WOLFENSTEIN_OFF_GAME_HANDLER_H

#include <client/sounds/audio_manager.h>
#include <client/graphics/game_screen.h>
#include "off_game_change_processor.h"
#include "in_game_event_generator.h"
#include "off_game_event_generator.h"
#include <common/map_parser.h>
#include <client/game/client_map_generator.h>

class OffGameHandler {
 private:
  GameScreen& screen;
  ClientMap& map;
  AudioManager audio_manager;
  OffGameChangeProcessor change_processor;
  bool player_ready = false;
  bool game_started = false;
  OffGameEventGenerator event_generator;
  bool& skip_stats;
  bool& game_running;
  bool server_down = false;
  int handleLoadingScreenEvent(SDL_Event event);
 public:
  OffGameHandler(GameScreen& _screen, ClientPlayer& player, ClientMap& _map,
                 SharedQueue<Change>& change_queue,
                 BlockingQueue<Event>& event_queue,
                 bool& _skip_stats, bool& _game_running);
  void displayLoadingScreen();
  void handleOffGame(const std::string& map_name);
  void initializeMap(const std::string& map_name);
};

#endif //TP_WOLFENSTEIN_OFF_GAME_HANDLER_H
