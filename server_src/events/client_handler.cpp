#include "server/events/client_handler.h"

ClientHandler::ClientHandler(NetworkConnection& _skt, SharedQueue<Event>& event_queue, int id) :
    skt(_skt),
    eventFactory(event_queue),
    alive(true),
    player_id(id) {
}

ClientHandler::~ClientHandler() {}

void ClientHandler::run() {
  std::cout << "[Client Handler] Starting.\n";
  while (alive) {
    std::string msg;
    try { skt.recv_msg(msg); }
    catch (NetworkError& e) { break; }
    eventFactory.createAndPushFromBytes(const_cast<char*>(msg.c_str()));
  }
  std::cout << "[Client Handler] Stopping.\n";
}

void ClientHandler::stop() {
  alive = false;
}

int ClientHandler::getPlayerId() const {
  return player_id;
}
