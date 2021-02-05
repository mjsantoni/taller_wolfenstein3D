//
// Created by andy on 5/2/21.
//

#include "client/game/client_game.h"


ClientGame::ClientGame(ServerUpdater& _server_updater,
                       ServerListener& _server_handler,
                       ClientMap& _map,
                       SharedQueue<Change>& change_queue) :
           server_updater(_server_updater),
           server_handler(_server_handler),
           game_handler(960, 600, real_map, _map, server_updater, change_queue),
           alive(true) {}

void ClientGame::run() {
    game_handler.start();
}

ClientGame::~ClientGame() {}

void ClientGame::stop() {
    alive = false;
}

bool ClientGame::isRunning() {
    return game_handler.isRunning();
}
