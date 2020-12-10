#ifndef TP_WOLFENSTEIN_POSITIONABLEHANDLER_H
#define TP_WOLFENSTEIN_POSITIONABLEHANDLER_H

#include "positionable.h"

class PositionableHandler {
public:
    PositionableHandler() {}

    Positionable createBlockingItem(std::string type);
    Positionable createItem(std::string type);
    Positionable createSpawns(std::string type);

    ~PositionableHandler() {}
};


#endif //TP_WOLFENSTEIN_POSITIONABLEHANDLER_H
