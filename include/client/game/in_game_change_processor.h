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
#include "off_game_event_handler.h"
#include "statistics_manager.h"
#include <client/game/client_map_generator.h>

class InGameChangeProcessor {
private:
    ClientMap& map;
    ClientPlayer& player;
    GameScreen& screen;
    AudioManager& audio_manager;
    SharedQueue<Change>& change_queue;
    bool game_over;
    bool& player_alive;
    bool& game_running;
    StatisticsManager& statistics_manager;
    std::vector<int> processEnemyAmmoChange(int enemy_id, int value);
    std::vector<int> processPlayerAmmoChange(int delta);
    std::vector<int> processEnemyHealthChange(int enemy_id, int delta);
    std::vector<int> processPlayerHealthChange(int delta);
public:
    InGameChangeProcessor(GameScreen& _screen,
                          ClientMap& _map,
                          ClientPlayer& _player,
                          SharedQueue<Change>& _change_queue,
                          AudioManager& _audio_manager,
                          StatisticsManager& _statistics_manager,
                          bool& _player_alive,
                          bool& _game_running);
    std::vector<int> processInGameChange(Change& change);
    void stop();
    void processInGameChanges();
    void processInGameChanges(std::vector<Change> changes);
    std::vector<int> displayStatisticsAndCloseGame();
    std::vector<int> processPostGameChanges(Change change);
    std::vector<int> processEnemyRespawning(int enemy_id);
    std::vector<int> processEnemyDying(int enemy_id);
};


#endif //TP_WOLFENSTEIN_IN_GAME_CHANGE_PROCESSOR_H
