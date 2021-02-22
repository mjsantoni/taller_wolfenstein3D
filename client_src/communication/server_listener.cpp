#include "client/communication/server_listener.h"

ServerListener::ServerListener(NetworkConnection& _skt,
                               SharedQueue<Change>& _change_queue) :
    skt(_skt),
    change_queue(_change_queue),
    change_factory(change_queue),
    alive(true) {
}

ServerListener::~ServerListener() {}

void ServerListener::run() {
  while (alive) {
    std::string msg;
    try { skt.recv_msg(msg); }
    catch (NetworkError& e) {
      change_queue.push(Change(GAME_OVER, INVALID, INVALID, INVALID));
      break;
    }
    Change change = change_factory.createFromBytes(const_cast<char*>(msg.c_str()));
    if (change.getChangeID() == GAME_OVER) stop();
    change_queue.push(change);
  }
}

void ServerListener::stop() {
    alive = false;
    skt.shutdownRecv();
}



