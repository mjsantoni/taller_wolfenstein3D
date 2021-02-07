//
// Created by andy on 6/2/21.
//

#ifndef TP_WOLFENSTEIN_CLIENT_MAP_GENERATOR_H
#define TP_WOLFENSTEIN_CLIENT_MAP_GENERATOR_H

#include <common/map_parser.h>
#include "client_map.h"
#include "image_manager.h"

class ClientMapGenerator {
private:
public:
    static void create(ClientMap& map, MapParser& parser);
    static void addWallsToMap(ClientMap &map, MapParser& map_parser);
    static void addObjectsToMap(ClientMap &map, MapParser &map_parser);
};



#endif //TP_WOLFENSTEIN_CLIENT_MAP_GENERATOR_H
