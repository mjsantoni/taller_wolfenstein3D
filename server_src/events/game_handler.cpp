#include "server/events/game_handler.h"

GameHandler::GameHandler(std::string map_path,
                         std::string config_path) :
        game(map_path, config_path),
        ep(game),
        eventQueue(Event()),
        changeQueue(Change()) {}

void GameHandler::run() {
    //ef.start();
    //ep.start();
    //proccess();
}
/*
void GameHandler::proccess() {
    while (game.isNotOver()) {
        Event event = eventQueue.pop();
        if (event.isNotValid()) continue;
        std::vector<Change> changes = ep.proccess(event);
        for (auto& change : changes) {
            changeQueue.push(change)
        //}

        //game.passTime();
        sleep(20);
    }
    stop();
}
*/
