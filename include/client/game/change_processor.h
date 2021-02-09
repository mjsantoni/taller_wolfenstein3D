#ifndef TP_WOLFENSTEIN_CHANGE_PROCESSOR_H
#define TP_WOLFENSTEIN_CHANGE_PROCESSOR_H

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
#include <client/game/client_map_generator.h>

class ChangeProcessor : public Thread {
private:
    ClientMap map;
    ClientPlayer& player;
    GameScreen screen;
    SharedQueue<Change>& change_queue;
    AudioManager audio_manager;
    std::atomic<bool> alive;
    std::atomic<bool>& game_started;
    std::atomic<bool>& player_ready;
    bool ready = false;
    std::string map_path;
    ClientPlayerInitializer player_initializer;
    OffGameChangeProcessor off_game_change_processor;
    OffGameEventHandler event_handler;
public:
    ChangeProcessor(ClientPlayer& _player,
                    SharedQueue<Change>& _change_queue,
                    std::atomic<bool>& _game_started,
                    std::atomic<bool>& _player_ready);
    void processInGameChange(Change& change);
    void run() override;
    void stop();
    ~ChangeProcessor();
    void receiveIdsFromServer();
    void addMapChange(Change& change);

    void displayIntro();

    int displayMatchModeMenu();

    void displayLevelSelectionMenu();

    void displayLoadingScreen();

    void initializePlayer();

    void setMapPath(int chosen_map);

    void initializeMap();

    void displayMenus();
};


#endif //TP_WOLFENSTEIN_CHANGE_PROCESSOR_H
