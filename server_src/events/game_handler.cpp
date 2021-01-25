#include "server/events/game_handler.h"
#include <unistd.h>

GameHandler::GameHandler(std::string map_path,
                         std::string config_path) :
        game(map_path, config_path),
        eventProcessor(game),
        eventQueue(Event()) {}

void GameHandler::run() {
    // tiene que ciclar hasta vacia o algo asi, no hacer 1 y dormir
    while (game.isNotOver() && alive) {
        int total_events = 0;
        Event event = eventQueue.pop();
        while (total_events < 5 && !event.isInvalid()) {
            /* Proceso a lo sumo 5 eventos */
            std::cout << "El evento que salio es de: " << event.getEventID() << "\n";
            std::vector<Change> changes = eventProcessor.process(event);
            for (auto& change : changes) {
                for (auto &client : clients_updater) {
                    client->update(change);
                }
            }
            event = eventQueue.pop();
            total_events++;
        }
        game.show();
        sleep(5);

    }
}

void GameHandler::addNewPlayer() {
    int id = game.connectPlayer();
    ClientHandler* handler = new ClientHandler(eventQueue,id);
    //ClientUpdater* updater = new ClientUpdater(id);
    handler->start();
    //updater->start();
    clients_handler.push_back(handler);
    //clients_updater.push_back(updater);
}

void GameHandler::stop() {
    for (auto& client : clients_handler) {
        client->stop();
        client->join();
    }
    alive = false;
}