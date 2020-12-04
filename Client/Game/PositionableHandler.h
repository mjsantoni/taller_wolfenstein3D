//
// Created by andy on 4/12/20.
//

#ifndef TP_WOLFENSTEIN_POSITIONABLEHANDLER_H
#define TP_WOLFENSTEIN_POSITIONABLEHANDLER_H


#include "Positionable.h"

class PositionableHandler {
public:
    static Positionable createPositionableFromType(int object_type,
                                                   std::string image_name);

};


#endif //TP_WOLFENSTEIN_POSITIONABLEHANDLER_H
