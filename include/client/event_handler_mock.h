//
// Created by andy on 11/12/20.
//

#ifndef TP_WOLFENSTEIN_EVENT_HANDLER_MOCK_H
#define TP_WOLFENSTEIN_EVENT_HANDLER_MOCK_H

#include "map_mock.h"
#include <SDL_events.h>

class EventHandlerMock {
public:
    explicit EventHandlerMock(MapMock& map);
    void putPlayerAt(std::string player_name, std::pair<int, int> coord);
    void handleEvent(SDL_Event event, ClientPlayer& player, bool& running, int& x, int& y);
    void calculateMovement(int& x, int& y, double alpha);
    bool movementAllowed(int& proj_x, int& proj_y, double angle_turn,
                         ClientPlayer& player, MapMock& map);
private:
    int mouse_position_x = 0;
    int step_size = 10;
    MapMock& map;
};



#endif //TP_WOLFENSTEIN_EVENT_HANDLER_MOCK_H
