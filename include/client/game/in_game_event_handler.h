//
// Created by andy on 30/1/21.
//

#ifndef TP_WOLFENSTEIN_IN_GAME_EVENT_HANDLER_H
#define TP_WOLFENSTEIN_IN_GAME_EVENT_HANDLER_H

#include <common/events.h>
#include <common/change.h>
#include "client_player.h"
#include "client/graphics/game_screen.h"
#include <common/shared_queue.h>

class InGameEventHandler {
 private:
  SharedQueue<Change>& change_queue;
 public:
  InGameEventHandler(SharedQueue<Change>& _change_queue);
  void handleCameraTurn(int direction);
};

#endif //TP_WOLFENSTEIN_IN_GAME_EVENT_HANDLER_H
