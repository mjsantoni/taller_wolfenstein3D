#ifndef TP_WOLFENSTEIN_POSITIONABLEHANDLER_H
#define TP_WOLFENSTEIN_POSITIONABLEHANDLER_H

#include "server/game/positionable.h"
#include "common/config_parser.h"

class PositionableHandler {
private:
    ConfigParser cp;
public:
    PositionableHandler(const std::string& _config_path);

    Positionable createBlockingItem(const std::string& type, int id);
    Positionable createItem(const std::string& type, int id);
    //Positionable createSpawns(std::string type);

    ~PositionableHandler() {}
};


#endif //TP_WOLFENSTEIN_POSITIONABLEHANDLER_H
