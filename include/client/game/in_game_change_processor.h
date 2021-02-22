#ifndef TP_WOLFENSTEIN_IN_GAME_CHANGE_PROCESSOR_H
#define TP_WOLFENSTEIN_IN_GAME_CHANGE_PROCESSOR_H

#include <client/game/client_map.h>
#include <client/game/client_player.h>
#include <client/graphics/game_screen.h>
#include <common/thread.h>
#include <common/shared_queue.h>
#include <client/sounds/audio_manager.h>
#include <common/map_parser.h>
#include "common/change.h"
#include "client/graphics/images.h"
#include "client_player_initializer.h"
#include "off_game_change_processor.h"
#include "statistics_manager.h"
#include <client/game/client_map_generator.h>
#include <client/game/timed_events.h>

class InGameChangeProcessor {
 private:
  ClientMap& map;
  ClientPlayer& player;
  GameScreen& screen;
  AudioManager& audio_manager;
  SharedQueue<Change>& change_queue;
  bool render_background_and_objects = true;
  bool skip_rendering = false;
  int mandatory_rendering_turns;
  bool game_over;
  bool& player_alive;
  bool& game_running;
  bool& skip_stats;
  int counter = 0;
  StatisticsManager& statistics_manager;
  void processEnemyAmmoChange(int enemy_id, int value);
  void processPlayerAmmoChange(int delta);
  void processEnemyHealthChange(int enemy_id, int delta);
  void processPlayerHealthChange(int delta);
  void processPostGameChanges(Change change);
  void processEnemyRespawning(int enemy_id);
  void processEnemyDying(int enemy_id);
  void processObjectRemoval(int object_id, int player_id);
 public:
  InGameChangeProcessor(GameScreen& _screen,
                        ClientMap& _map,
                        ClientPlayer& _player,
                        SharedQueue<Change>& _change_queue,
                        AudioManager& _audio_manager,
                        StatisticsManager& _statistics_manager,
                        bool& _player_alive,
                        bool& _game_running,
                        bool& _skip_stats);
  void processChange(Change& change);
  void stop();
  void processInGameChanges();
  void updateMandatoryRenderingTurns(int new_value);
  void playAttackingSound(int players_weapon, double distance_ratio);
};

#endif //TP_WOLFENSTEIN_IN_GAME_CHANGE_PROCESSOR_H
