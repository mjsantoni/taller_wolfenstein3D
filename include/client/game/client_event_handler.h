//
// Created by andy on 30/1/21.
//

#ifndef TP_WOLFENSTEIN_CLIENT_EVENT_HANDLER_H
#define TP_WOLFENSTEIN_CLIENT_EVENT_HANDLER_H

#include <common/events.h>
#include <common/change.h>
#include "client_player.h"
#include "client/graphics/game_screen.h"
#include <common/shared_queue.h>

class ClientEventHandler {
private:
    SharedQueue<Change>& change_queue;
public:
    ClientEventHandler(SharedQueue<Change>& _change_queue);
    void handleCameraTurn(int direction);
    void handlePlayerShooting();
};



#endif //TP_WOLFENSTEIN_CLIENT_EVENT_HANDLER_H
