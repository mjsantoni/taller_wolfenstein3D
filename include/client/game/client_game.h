//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_GAME_H
#define TP_WOLFENSTEIN_CLIENT_GAME_H

#include <SDL.h>
#include "client/graphics/ray_caster.h"
#include "client/graphics/sdl_window.h"
#include "client/graphics/sdl_texture.h"
#include "client/sdl_exception.h"
#include "client_map.h"
#include "sdl_audio_player.h"
#include "client/graphics/game_screen.h"
#include "in_game_event_handler.h"
#include "in_game_event_generator.h"
#include "in_game_change_processor.h"
#include <vector>
#include <common/change.h>
#include <common/shared_queue.h>
#include <common/map_parser.h>
#include <common/config_parser.h>
#include <client/sounds/audio_manager.h>
#include "client_map_generator.h"
#include "client_player_initializer.h"
#include "off_game_change_processor.h"
#include "off_game_handler.h"
#include <common/connection_exception.h>

class ClientGame {
 private:
  GameScreen screen;
  ClientMap map;
  ClientPlayer player = ClientPlayer("Player 1");
  AudioManager audio_manager;
  bool game_running;
  InGameEventGenerator event_generator;
  InGameEventHandler event_handler;
  InGameChangeProcessor change_processor;
  StatisticsManager statistics_manager;
  bool game_started;
  bool player_ready;
  bool player_alive = true;
  bool player_quitted = false;
  OffGameHandler off_game_handler;
  ClientPlayerInitializer player_initializer;
 public:
  ClientGame(SharedQueue<Change>& change_queue,
             BlockingQueue<Event>& event_queue);
  ~ClientGame();
  void startGame(const std::string& map_name);
  void killPlayer();
  void respawnPlayer();
  bool isRunning();
  void initializePlayer();
  void initializeMap();
  void displayConnectionErrorScreen();
  void processGame();
  void displayStatistics();

  void displayResultScreen(int game_result);

  int processGameResult();
};

#endif //TP_WOLFENSTEIN_CLIENT_GAME_H
