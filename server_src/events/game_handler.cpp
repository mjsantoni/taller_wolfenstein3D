#include "server/events/game_handler.h"
#include <unistd.h>

GameHandler::GameHandler(std::string map_path,
                         std::string config_path) :
        game(map_path, config_path),
        eventProcessor(game),
        eventQueue(Event()) {}

void GameHandler::run() {
    // tiene que ciclar hasta vacia o algo asi, no hacer 1 y dormir
    while (game.isNotOver()) {
        Event event = eventQueue.pop();
        if (event.isInvalid()) continue;
        std::vector<Change> changes = eventProcessor.process(event);
        for (auto& change : changes) {
            for (auto& client : clients_updater) {
                client->update(change);
            }
        }
        //game.passTime();
        sleep(5);
    }
    //stop();
}

