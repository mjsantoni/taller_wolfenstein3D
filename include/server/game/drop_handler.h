#ifndef TP_WOLFENSTEIN_DROP_HANDLER_H
#define TP_WOLFENSTEIN_DROP_HANDLER_H

#include "server/game/config_parser.h"
#include "server/game/map.h"


class DropHandler {
private:
    ConfigParser configParser;

public:
    DropHandler(std::string config_path);
    ~DropHandler();

    void processDrops(const std::pair<std::pair<std::string, int>, int>& drops, Map &map, const Coordinate& pos);
};


#endif //TP_WOLFENSTEIN_DROP_HANDLER_H
