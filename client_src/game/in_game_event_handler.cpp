//
// Created by andy on 30/1/21.
//

#include "client/game/in_game_event_handler.h"
#

void InGameEventHandler::handleCameraTurn(int direction) {
    Change change(CL_UPDATE_DIRECTION, 0, 0, direction);
    change_queue.push(change);
    //player.updateDirection(direction);
}

InGameEventHandler::InGameEventHandler(SharedQueue<Change>& _change_queue) :
                                       change_queue(_change_queue){
}