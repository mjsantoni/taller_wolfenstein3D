//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_EVENTHANDLER_H
#define TP_WOLFENSTEIN_EVENTHANDLER_H


#include "map.h"

class EventHandler {
public:
    void handleEvent(SDL_Event event, Player& player, Map& map, bool& running, int& x, int& y);
    void handleMouseEvent(SDL_Event event, Player& player, SdlWindow& window);
    void getMousePosition();
    void calculateMovement(int& x, int& y, double alpha);
    bool movementAllowed(int& proj_x, int& proj_y, double angle_turn,
    Player& player, Map& map);
private:
    int mouse_position_x = 0;
    int step_size = 50;
};


#endif //TP_WOLFENSTEIN_EVENTHANDLER_H
