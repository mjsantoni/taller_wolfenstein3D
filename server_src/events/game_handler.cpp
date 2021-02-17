#include "server/events/game_handler.h"
#include <unistd.h>

#define MAX_EVENTS 100

GameHandler::GameHandler(const std::string &map_path, const std::string &config_path, int _players_n, int _bots_n,
                         int _game_id) :
        eventQueue(Event()),
        botsManager(eventQueue),
        game(map_path, config_path, botsManager, _players_n),
        eventProcessor(game, config_path),
        alive(true),
        can_join_player(true),
        players_n(_players_n),
        bots_n(_bots_n),
        game_id(_game_id) {}

void GameHandler::run() {
    std::cout << "[Game Handler " << game_id << "] Started.\n";
    waitInLobby();
    addBots();
    sleep(1);
    std::cout << "[Game Handler " << game_id << "] Game start.\n";
    Change change(GAME_START, INVALID, INVALID, INVALID, true);
    clientsManager.notifyClients(change);
    while (game.isNotOver() && alive) {
        int total_events = 0;
        while (total_events < MAX_EVENTS) {
            Event event = eventQueue.pop();
            if (event.isInvalid()) break;
            std::vector<Change> changes = eventProcessor.process(event);
            notifyClients(changes);
            total_events++;
            // aca va otro sleep?
        }
        std::vector<Change> game_changes = game.passTime();
        notifyClients(game_changes);
        game.releaseBots();
        usleep(60000);
    }
    std::cout << "[Game Handler " << game_id << "] Game end. Displaying top scores.\n";
    endGame();
}

void GameHandler::notifyClients(std::vector<Change>& changes) {
    for (auto& change : changes) {
        clientsManager.notifyClients(change);
    }
}

void GameHandler::addBots() {
    std::cout << "[Game Handler " << game_id << "] Adding bots.\n";
    for (int i = 0; i < bots_n; i++) {
        game.addBot();
    }
    Change change(TOTAL_PLAYERS_CONNECTED, game.getPlayersAlive(), INVALID, INVALID, true);
    clientsManager.notifyClients(change);
}

void GameHandler::waitInLobby() {
    std::cout << "[Game Handler " << game_id << "] Lobby started.\n";
    while (!game.isReady() && alive) {
        Event event = eventQueue.pop();
        usleep(150000);
        if (event.isInvalid()) continue;
        if (event.getEventID() != CONNECT_PLAYER && event.getEventID() != PLAYER_READY) continue;
        std::vector<Change> changes = eventProcessor.process(event);
        notifyClients(changes);
    }
    can_join_player = false;
    std::cout << "[Game Handler " << game_id << "] Lobby finished.\n";
}

void GameHandler::notifyTop(std::vector<std::pair<int,int>> top, int change_id) {
    std::vector<Change> changes;
    for (int i = 0; i < top.size(); i++) {
        changes.emplace_back(change_id, top[i].first, top[i].second, i);
    }
    notifyClients(changes);
}

void GameHandler::sendTops() {
    std::vector<std::pair<int,int>> kills = game.getTop("kills", 5);
    std::vector<std::pair<int,int>> bullets = game.getTop("bullets", 5);
    std::vector<std::pair<int,int>> scores = game.getTop("scores", 5);

    notifyTop(kills, TOP_KILLER);
    notifyTop(bullets, TOP_SHOOTER);
    notifyTop(scores, TOP_SCORER);
}

void GameHandler::addNewPlayer(NetworkConnection socket) {
    std::pair<int,std::unordered_map<Coordinate, Positionable, Coordinate::HashFunction>> data = game.connectPlayer();
    int id = data.first;
    std::cout << "[Game Handler " << game_id << "] New Player connected -> Id: " << id << std::endl;
    std::unordered_map<Coordinate, Positionable, Coordinate::HashFunction> map = data.second;
    clientsManager.addNewPlayer(std::move(socket), id, eventQueue, map);
}

void GameHandler::endGame() {
    sendTops();
    Change change(GAME_OVER, 0, 0, 0, true);
    clientsManager.notifyClients(change);
    sleep(3); // Esto no deberia estar
    clientsManager.killPlayers();
    std::cout << "[Game Handler " << game_id << "] Stopping.\n";
    alive = false;
}

void GameHandler::stop() {
    alive = false;
}

bool GameHandler::canJoinPlayer() {
    return can_join_player;
}

bool GameHandler::ended() {
    return alive;
}
