//
// Created by andy on 30/1/21.
//

#include "client/game/client_event_handler.h"

void ClientEventHandler::handleWeaponChange(int weapon_number) {
    player.changeWeapon(weapon_number);
    //screen.render();
}

void ClientEventHandler::handleCameraTurn(int direction) {
    player.updateDirection(direction);
}

ClientEventHandler::ClientEventHandler(ClientPlayer &_player,
                                       GameScreen& _screen) :
                                       player(_player),
                                       screen(_screen) {}