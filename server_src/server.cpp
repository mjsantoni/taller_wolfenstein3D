#include <algorithm>
#include "server/server.h"

Server::Server(NetworkAcceptor socket) :
    networkAcceptor(std::move(socket)),
    accepting_connections(true) {
}

void Server::run() {
  std::cout << "[Server] Started.\n";
  while (accepting_connections) {
    try {
      NetworkConnection socket = std::move(networkAcceptor.acceptConnection());
      if (!socket.isValid()) continue;
      if (!accepting_connections) break;
      ServerMenuHandler* acceptor = new ServerMenuHandler(std::move(socket), matches);
      handlers.push_back(acceptor);
      acceptor->start();
    } catch (const NetworkError& e) { continue; }
    matches.killDead();
  }
  closeHandlers();
  matches.stopGames();
  std::cout << "[Server] Finished all in-progress games.\n";
}

void Server::stop() {
  accepting_connections = false;
  networkAcceptor.closeSocket();
}

void Server::closeHandlers() {
  std::cout << "[Server] Closing Menu Handlers.\n";
    for (auto& handler : handlers) {
        handler->stop();
        handler->join();
        delete handler;
    }
}

Server::~Server() {}
