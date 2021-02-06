#include "server/events/game_handler.h"
#include <unistd.h>

#define MAX_EVENTS 100

GameHandler::GameHandler(std::string map_path,
                         std::string config_path) :
        eventQueue(Event()),
        botsManager(eventQueue),
        game(map_path, config_path, botsManager),
        eventProcessor(game, config_path),
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

        while (total_events < MAX_EVENTS) {
            Event event = eventQueue.pop();
            if (event.isInvalid()) {
                std::cout << "INVALIDOOOO\n";
                break;
            }
            std::cout << "El evento que salio es de: " << event.getEventID() << "\n";
            std::vector<Change> changes = eventProcessor.process(event);
            notifyClients(changes);
            total_events++;
        }
        //game.show();
        std::vector<Change> game_changes = game.passTime();
        notifyClients(game_changes);
        game.releaseBots();
        sleep(2);
    }
    std::cout << "Termino la partida!!!!\n";
}

void GameHandler::notifyClients(std::vector<Change>& changes) {

    for (auto& change : changes) {
        clientsManager.notifyClients(change);
    }
}

void GameHandler::addNewPlayer(NetworkConnection socket) {
    std::pair<int,std::map<Coordinate, Positionable>> data = game.connectPlayer();
    int id = data.first;
    std::cout << "Player id " << id << std::endl;
    std::map<Coordinate, Positionable> map = data.second;
    clientsManager.addNewPlayer(std::move(socket), id, eventQueue, map);
    //eventQueue.push(Event(CONNECT_PLAYER, id, INVALID));
    // enviar el mapa al cliente a traves del client updater
}

void GameHandler::stop() {
    clientsManager.killPlayers();
    alive = false;
}