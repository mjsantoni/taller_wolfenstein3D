//
// Created by andy on 8/2/21.
//

#ifndef TP_WOLFENSTEIN_OFF_GAME_CHANGE_PROCESSOR_H
#define TP_WOLFENSTEIN_OFF_GAME_CHANGE_PROCESSOR_H

#include <common/change.h>
#include "client_map.h"
#include "client_player.h"
#include <common/shared_queue.h>

class OffGameChangeProcessor {
 private:
  ClientMap& map;
  ClientPlayer& player;
  bool& player_ready;
  bool& game_started;
  SharedQueue<Change>& change_queue;
 public:
  explicit OffGameChangeProcessor(ClientMap& _map, ClientPlayer& _player,
                                  SharedQueue<Change>& _change_queue,
                                  bool& _game_started, bool& _player_ready);
  void processOffGameChanges();
  void addMapChange(Change& change);

};

#endif //TP_WOLFENSTEIN_OFF_GAME_CHANGE_PROCESSOR_H
