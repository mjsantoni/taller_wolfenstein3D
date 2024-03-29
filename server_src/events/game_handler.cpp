#include "server/events/game_handler.h"
#include <unistd.h>

#define MAX_EVENTS 100
#define TICK_RATE 60000

GameHandler::GameHandler(const std::string& map_path, const std::string& config_path,
                         int _min_players_in_lobby,
                         int _max_players, int _max_bots,
                         int _game_id, int _game_duration) :
    eventQueue(Event()),
    botsManager(eventQueue),
    game(map_path, config_path, botsManager, _min_players_in_lobby,
         _game_duration, _max_players),
    eventProcessor(game, config_path),
    alive(true),
    can_join_player(true),
    min_players_in_lobby(_min_players_in_lobby),
    max_bots(_max_bots),
    id(_game_id),
    game_duration(_game_duration) {
  name = map_path;
}

void GameHandler::run() {
  std::string started = "[Game Handler " + std::to_string(id) + "] Started.\n";
  std::cout << started;
  waitInLobby();
  addBots();
  std::string startGame = "[Game Handler " + std::to_string(id) + "] Game startGame.\n";
  std::cout << startGame;
  Change change(GAME_START, INVALID, INVALID, INVALID, true);
  clientsManager.notifyClients(change);

  while (!game.isOver() && alive) {
    auto start = std::chrono::system_clock::now();
    int total_events = 0;
    while (total_events < MAX_EVENTS) {
      Event event = eventQueue.pop();
      if (event.isInvalid()) break;
      std::vector<Change> changes = eventProcessor.process(event);
      notifyClients(changes);
      total_events++;
    }
    std::vector<Change> game_changes = game.passTime();
    notifyClients(game_changes);
    game.releaseBots();
    std::chrono::duration<double> elapsed = (std::chrono::system_clock::now() - start);
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    if (time > TICK_RATE) continue;
    usleep(TICK_RATE - time);
  }

  std::string gameEnd = "[Game Handler " + std::to_string(id) + "] Game end. Displaying top scores.\n";
  std::cout << gameEnd;
  endGame();
}

void GameHandler::notifyClients(std::vector<Change>& changes) {
  for (auto& change : changes) {
    clientsManager.notifyClients(change);
  }
}

void GameHandler::addBots() {
  std::string gameEnd = "[Game Handler " + std::to_string(id) + "] Adding bots.\n";
  std::cout << gameEnd;
  for (int i = 0; i < max_bots; i++) {
    game.addBot();
  }
  Change change(TOTAL_PLAYERS_CONNECTED, game.getPlayersAlive(), INVALID, INVALID, true);
  clientsManager.notifyClients(change);
}

void GameHandler::waitInLobby() {
  std::string lobbyStart = "[Game Handler " + std::to_string(id) + "] Lobby started.\n";
  std::cout << lobbyStart;

  while (!game.isReady() && alive) {
    Event event = eventQueue.pop();
    usleep(TICK_RATE);
    if (event.isInvalid()) continue;
    if (event.getEventID() != CONNECT_PLAYER && event.getEventID() != PLAYER_READY) continue;
    std::vector<Change> changes = eventProcessor.process(event);
    notifyClients(changes);
  }

  can_join_player = false;
  std::string lobbyEnd = "[Game Handler " + std::to_string(id) + "] Lobby finished.\n";;
  std::cout << lobbyEnd;
}

void GameHandler::notifyTop(std::vector<std::pair<int, int>> top, int change_id) {
  std::vector<Change> changes;
  for (int i = 0; i < top.size(); i++) {
    changes.emplace_back(change_id, top[i].first, top[i].second, i);
  }
  notifyClients(changes);
}

void GameHandler::sendTops() {
  std::vector<std::pair<int, int>> kills = game.getTop("kills", 5);
  std::vector<std::pair<int, int>> bullets = game.getTop("bullets", 5);
  std::vector<std::pair<int, int>> scores = game.getTop("scores", 5);

  notifyTop(kills, TOP_KILLER);
  notifyTop(bullets, TOP_SHOOTER);
  notifyTop(scores, TOP_SCORER);
}

void GameHandler::addNewPlayer(NetworkConnection socket) {
  std::pair<int, std::unordered_map<Coordinate, Positionable, Coordinate::HashFunction>> data = game.connectPlayer();
  int player_id = data.first;
  std::string newConnected =
      "[Game Handler " + std::to_string(id) + "] New Player connected -> Id: " + std::to_string(player_id);
  std::cout << newConnected;
  std::unordered_map<Coordinate, Positionable, Coordinate::HashFunction> map = data.second;
  clientsManager.addNewPlayer(std::move(socket), player_id, eventQueue, map);
}

void GameHandler::endGame() {
  sendTops();
  Change change(GAME_OVER, 0, 0, 0, true);
  clientsManager.notifyClients(change);
  clientsManager.killPlayers();
  std::string stopping = "[Game Handler " + std::to_string(id) + "] Stopping.\n";
  std::cout << stopping;
  alive = false;
}

void GameHandler::stop() {
  alive = false;
}

bool GameHandler::canJoinPlayer() {
  return can_join_player;
}

bool GameHandler::ended() {
  return !alive;
}

std::string GameHandler::getInformation() {
  std::string plain_name = name.substr(0, name.size() - 5);
  return plain_name + "/" + std::to_string(id);
}

