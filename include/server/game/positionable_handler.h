#ifndef TP_WOLFENSTEIN_POSITIONABLEHANDLER_H
#define TP_WOLFENSTEIN_POSITIONABLEHANDLER_H

#include "server/entities/positionable.h"
#include "common/config_parser.h"

class PositionableHandler {

public:
    PositionableHandler();

    Positionable createBlockingItem(const std::string& type, int id);
    Positionable createItem(const std::string& type, int id);
    //Positionable createSpawns(std::string type);

    ~PositionableHandler() {}
};


#endif //TP_WOLFENSTEIN_POSITIONABLEHANDLER_H
