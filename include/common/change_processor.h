#ifndef TP_WOLFENSTEIN_CHANGE_PROCESSOR_H
#define TP_WOLFENSTEIN_CHANGE_PROCESSOR_H

#include <client/client_map.h>
#include <client/client_player.h>
#include <client/game_screen.h>
#include "common/change.h"
#include "client/images.h"

class ChangeProcessor {
private:
    ClientMap& map;
    ClientPlayer& player;
    GameScreen& screen;
public:
    ChangeProcessor(ClientMap& _map, ClientPlayer& _player,GameScreen& _screen);
    void process(Change& change);

};


#endif //TP_WOLFENSTEIN_CHANGE_PROCESSOR_H
