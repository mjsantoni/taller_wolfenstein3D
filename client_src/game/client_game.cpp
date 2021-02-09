//
// Created by andy on 5/2/21.
//

#include "client/game/client_game.h"


ClientGame::ClientGame(SharedQueue<Change>& change_queue,
                       BlockingQueue<Event>& event_queue) :

           game_handler(960, 600, change_queue, event_queue),
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
