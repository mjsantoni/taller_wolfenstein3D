#ifndef TP_WOLFENSTEIN_POSITIONABLEHANDLER_H
#define TP_WOLFENSTEIN_POSITIONABLEHANDLER_H

#include "positionable.h"
#include "common/config_parser.h"

class PositionableHandler {
private:
    ConfigParser cp;
public:
    PositionableHandler(std::string _config_path);

    Positionable createBlockingItem(std::string type, int id);
    Positionable createItem(std::string type, int id);
    //Positionable createSpawns(std::string type);

    ~PositionableHandler() {}
};


#endif //TP_WOLFENSTEIN_POSITIONABLEHANDLER_H
