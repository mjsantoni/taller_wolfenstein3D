#include "client/game/client.h"
#include <iostream>

Client::Client(NetworkConnection& skt, const std::string& config_file) :
    running(true),
    change_queue(Change()),
    event_queue(Event()),
    server_updater(skt, event_queue),
    server_listener(skt, change_queue),
    config_parser(config_file) {
}

void Client::startGame(const std::string& map_name) {
  std::pair<int, int> screen_res = config_parser.getResolution();
  int screen_width = screen_res.first;
  int screen_height = screen_res.second;
  try {
    ClientGame game(screen_width, screen_height, change_queue, event_queue);
    server_updater.start();
    server_listener.start();
    try {
      game.startGame(map_name);
    }
    catch (ConnectionException& e) {
      game.displayConnectionErrorScreen();
    }
    game.displayStatistics();
  }
  catch (SdlException& e) {
    std::cout << e.what() << std::endl;
  }
  running = false;
}

Client::~Client() {
  server_updater.stop();
  server_listener.stop();
  server_updater.join();
  server_listener.join();
}