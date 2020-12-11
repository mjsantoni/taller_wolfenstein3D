#include "server/server_main.h"
#include "server/map_generator.h"
#include "server/map_parser.h"
#include "server/map.h"

Server::Server(std::string _path) : path(_path) {
    MapParser parser(path);
    MapGenerator generator(parser);
    Map map = generator.create(8); // Player max spawn count
    map.show();
}

Server::~Server() {
}
