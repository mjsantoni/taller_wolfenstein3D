#include "client/game/client.h"
#include <iostream>

Client::Client(NetworkConnection& skt) : running(true),
                                         change_queue(Change()),
                                         event_queue(Event()),
                                         server_updater(skt, event_queue),
                                         server_listener(skt, change_queue) {
}

void Client::startGame(const std::string& map_name) {
  try {
    ClientGame game(change_queue, event_queue);
    server_updater.start();
    server_listener.start();
    try {
      game.startGame(map_name);
    }
    catch (ConnectionException& e) {
      game.displayConnectionErrorScreen();
    }
    game.displayStatistics();
    server_updater.stop();
    server_listener.stop();
    server_updater.join();
    server_listener.join();
  }
  catch (SdlException& e) {
    std::cout << e.what() << std::endl;
  }
  running = false;
}

void Client::stop() {}

bool Client::isRunning() {
  return running;
}