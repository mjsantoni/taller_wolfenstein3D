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
    while (!game.isReady()) {
        Event event = eventQueue.pop();
        if (event.isInvalid()) continue;
        if (event.getEventID() != CONNECT_PLAYER && event.getEventID() != PLAYER_READY) continue;
        std::vector<Change> changes = eventProcessor.process(event);
        notifyClients(changes);
    }
    std::cout << "Termino el lobby\n";
    //sleep(3); // para cargar los HUDs y eso ?
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
        for (auto &client : clients)
            client->update(change);
    }
}

void GameHandler::addNewPlayer(NetworkConnection socket) {
    int id = game.connectPlayer();
    Client* client = new Client(std::move(socket),eventQueue,id);
    clients.push_back(client);
}

void GameHandler::stop() {
    for(auto& client : clients) {
        client->stop();
        delete client;
    }
    alive = false;
}