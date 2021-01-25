#ifndef TP_WOLFENSTEIN_DROP_HANDLER_H
#define TP_WOLFENSTEIN_DROP_HANDLER_H

#include "server/game/config_parser.h"
#include "server/game/map.h"
#include "server/game/drop.h"

class DropHandler {
private:
    ConfigParser configParser;
    Map& map;

public:
    DropHandler(std::string config_path, Map &_map);
    ~DropHandler();

    void processDrops(const std::vector<Drop> &drops);
};


#endif //TP_WOLFENSTEIN_DROP_HANDLER_H
