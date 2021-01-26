#include "server/events/game_handler.h"
#include <unistd.h>

#define MAX_EVENTS 5

GameHandler::GameHandler(std::string map_path,
                         std::string config_path) :
        game(map_path, config_path),
        eventProcessor(game, config_path),
        eventQueue(Event()),
        alive(true) {}

void GameHandler::run() {
    while (game.isNotOver() && alive) {
        int total_events = 0;
        Event event = eventQueue.pop();
        while (total_events < MAX_EVENTS && !event.isInvalid()) {
            //std::cout << "El evento que salio es de: " << event.getEventID() << "\n";
            std::vector<Change> changes = eventProcessor.process(event);
            notifyClients(changes);
            event = eventQueue.pop();
            total_events++;
        }
        //game.show();
        std::vector<Change> game_changes = game.passTime();
        notifyClients(game_changes);
        sleep(5);
    }
}

void GameHandler::notifyClients(std::vector<Change>& changes) {
    for (auto& change : changes) {
        for (auto &client : clients_updater)
            client->update(change);
    }
}


void GameHandler::addNewPlayer(int fd) {
    sockets.push_back(fd);
    int id = game.connectPlayer();
    ClientHandler* handler = new ClientHandler(eventQueue,id);
    ClientUpdater* updater = new ClientUpdater(fd, id);
    handler->start();
    updater->start();
    clients_handler.push_back(handler);
    clients_updater.push_back(updater);
}

void GameHandler::stop() {
    for (auto& client : clients_handler) {
        client->stop();
        client->join();
    }
    for (auto& client : clients_updater) {
        client->stop();
        client->join();
    }
    alive = false;
}