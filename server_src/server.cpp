//
// Created by ubuntu on 9/12/20.
//

#include "server/server.h"
#include "server/map_generator.h"
#include "server/map_parser.h"
#include "client/client.h"

Server::Server(std::string path) {
    MapParser parser(path);
    MapGenerator generator(parser);
    std::pair<int,int> dimensions = parser.getDimensions();

    int width = dimensions.first;
    int height = dimensions.second;

    Client(width, height, generator.getWalls());
}
Server::~Server() {

}
