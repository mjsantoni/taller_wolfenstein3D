#ifndef TP_WOLFENSTEIN_CHANGE_PROCESSOR_H
#define TP_WOLFENSTEIN_CHANGE_PROCESSOR_H

#include <client/game/client_map.h>
#include <client/game/client_player.h>
#include <client/graphics/game_screen.h>
#include "common/change.h"
#include "client/graphics/images.h"

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
