//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_CLIENTEVENTHANDLER_H
#define TP_WOLFENSTEIN_CLIENTEVENTHANDLER_H

#include "server/map.h"

class ClientEventHandler {
public:
    ClientEventHandler(Map& map);
    void handleEvent(SDL_Event event, Player& player, bool& running, int& x, int& y);
    void handleMouseEvent(SDL_Event event, Player& player, SdlWindow& window);
    void getMousePosition();
    void calculateMovement(int& x, int& y, double alpha);
    bool movementAllowed(int& proj_x, int& proj_y, double angle_turn,
                         Player& player, Map& map);
    void putPlayerAt(std::string player_name, std::pair<int, int> position);
private:
    int mouse_position_x = 0;
    int step_size = 50;
    Map map;
};


#endif //TP_WOLFENSTEIN_CLIENTEVENTHANDLER_H