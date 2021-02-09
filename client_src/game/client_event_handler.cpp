//
// Created by andy on 30/1/21.
//

#include "client/game/client_event_handler.h"
#

void ClientEventHandler::handleCameraTurn(int direction) {
    Change change(CL_UPDATE_DIRECTION, 0, 0, direction);
    change_queue.push(change);
    //player.updateDirection(direction);
}

ClientEventHandler::ClientEventHandler(SharedQueue<Change>& _change_queue) :
                                       change_queue(_change_queue){
}

void ClientEventHandler::handlePlayerShooting() {
    Change change(CL_PLAYER_SHOOTING, 0, 0, 0);
    change_queue.push(change);
}