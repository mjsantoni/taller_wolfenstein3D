#ifndef TP_WOLFENSTEIN_CHANGE_PROCESSOR_H
#define TP_WOLFENSTEIN_CHANGE_PROCESSOR_H

#include <client/game/client_map.h>
#include <client/game/client_player.h>
#include <client/graphics/game_screen.h>
#include <common/thread.h>
#include <common/shared_queue.h>
#include "common/change.h"
#include "client/graphics/images.h"

class ChangeProcessor : public Thread {
private:
    ClientMap& map;
    ClientPlayer& player;
    GameScreen& screen;
    SharedQueue<Change>& change_queue;
    std::atomic<bool> alive;
public:
    ChangeProcessor(ClientMap& _map, ClientPlayer& _player, GameScreen& _screen,
                    SharedQueue<Change>& _change_queue);
    void processChange(Change& change);
    void run() override;
    void stop();
    ~ChangeProcessor();
    void receiveMapFromServer();
    void addMapChange(Change& change);
};


#endif //TP_WOLFENSTEIN_CHANGE_PROCESSOR_H
