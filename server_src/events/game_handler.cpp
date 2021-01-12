#include "server/game/game_handler.h"

GameHandler::GameHandler(std::string path) : game(path, path), eh(eq), ep(game,eq) {}

void GameHandler::run() {
    //eh.start();
    //ep.start();
    //proccess();
}
/*
void GameHandler::proccess() {
    while (game.isNotOver()) {
        while (eq.isNotEmpty()) {
            Event event = eq.pop();
            std::vector<Change> changes = ep.proccess(event);
            for (auto& change : changes) {
                if (change.isGlobal()) notify_clients(change);
                else notify(change.id,change);
            }
        }
        sleep(20);
    }
    stop();
}
*/
