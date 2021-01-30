//
// Created by andy on 30/1/21.
//

#ifndef TP_WOLFENSTEIN_CLIENT_EVENT_HANDLER_H
#define TP_WOLFENSTEIN_CLIENT_EVENT_HANDLER_H

#include <common/events.h>
#include "client_player.h"
#include "client/graphics/game_screen.h"

class ClientEventHandler {
private:
    ClientPlayer& player;
    GameScreen& screen;
public:
    ClientEventHandler(ClientPlayer& _player, GameScreen& _screen);
    void handleWeaponChange(int weapon_number);
    void handleCameraTurn(int direction);
};


#endif //TP_WOLFENSTEIN_CLIENT_EVENT_HANDLER_H
