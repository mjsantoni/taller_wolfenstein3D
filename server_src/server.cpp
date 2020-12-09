#include "server/server.h"
#include "server/map_generator.h"
#include "server/map_parser.h"
#include "client/client.h"

Server::Server(std::string _path) : path(_path) {

}

void Server::run() {
    MapParser parser(path);
    MapGenerator generator(parser);
    std::pair<int,int> dimensions = parser.getDimensions();

    int width = dimensions.first;
    int height = dimensions.second;
    std::vector<std::pair<int,int>> walls = generator.getWalls();
    Client* client = new Client(width, height, walls);
    client->start();
    while (playing) {}
    client->join();
    delete client;
}

void Server::stop() {
    playing = false;
}
Server::~Server() {
}
