#include "server/events/client_updater.h"

ClientUpdater::ClientUpdater(NetworkConnection& _sk,
                             int id,
                             std::unordered_map<Coordinate, Positionable, Coordinate::HashFunction> _map) :
    skt(_sk),
    change_queue(Change()),
    player_id(id),
    alive(true),
    map(_map) {
}

ClientUpdater::~ClientUpdater() { change_queue.close(); }

void ClientUpdater::sendMap() {
  std::cout << "[Client Updater] Sending map.\n";
  for (auto& elem : map) {
    int x = elem.first.x;
    int y = elem.first.y;
    int id = elem.second.getId();
    Change change(MAP_INITIALIZER, id, x, y, false);
    skt.send_msg(change.serialize());
  }
}

void ClientUpdater::run() {
  std::cout << "[Client Updater] Starting.\n";
  skt.send_msg(Change(ADD_PLAYER, player_id, INVALID, INVALID, false).serialize());
  /* Envio el ID primero */
  sendMap();
  /* Despues el mapa */
  while (true) {
    Change change = change_queue.pop();
    if (change.isInvalid() && alive) continue;
    if (change.isInvalid() && !alive) break;
    if (change.isGlobal() || change.getPlayerID() == player_id) {
      try {
        skt.send_msg(change.serialize());
      } catch (NetworkError& e) { break; }
    }
  }
  std::cout << "[Client Updater] Stopping.\n";
}

void ClientUpdater::update(Change change) { change_queue.push(change); }

void ClientUpdater::stop() {
  alive = false;
  change_queue.push(Change());
}

int ClientUpdater::getPlayerId() const {
  return player_id;
}
