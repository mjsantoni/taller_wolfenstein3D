//
// Created by andy on 8/2/21.
//

#ifndef TP_WOLFENSTEIN_CLIENT_PLAYER_INITIALIZER_H
#define TP_WOLFENSTEIN_CLIENT_PLAYER_INITIALIZER_H

#include <common/config_parser.h>
#include "client_player.h"

class ClientPlayerInitializer {
 private:
  ConfigParser config_parser;
 public:
  ClientPlayerInitializer();
  void initializePlayer(ClientPlayer& player);
};

#endif //TP_WOLFENSTEIN_CLIENT_PLAYER_INITIALIZER_H
