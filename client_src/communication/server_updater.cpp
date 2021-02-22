#include "client/communication/server_updater.h"

ServerUpdater::ServerUpdater(NetworkConnection& _sk,
                             BlockingQueue<Event>& _event_queue) :
    skt(_sk),
    event_queue(_event_queue),
    alive(true) {
}

ServerUpdater::~ServerUpdater() {}

void ServerUpdater::run() {
  while (alive) {
    Event event = event_queue.pop();
    if (event.isInvalid()) continue;
    try { skt.send_msg(event.serialize()); }
    catch (NetworkError& e) { break; }
    //std::cout << "El mensaje " << event.serialize() << " se envio al socket\n";
  }
}

void ServerUpdater::stop() {
  alive = false;
  event_queue.close();
}
