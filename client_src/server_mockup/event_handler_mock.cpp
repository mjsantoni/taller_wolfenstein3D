//
// Created by andy on 11/12/20.
//

#include "client/event_handler_mock.h"

//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include "client/event_handler_mock.h"

EventHandlerMock::EventHandlerMock(MapMock &map) : map(map) {
}

void EventHandlerMock::putPlayerAt(std::string player_name, std::pair<int, int> coord) {
    map.putPlayerAt(player_name, coord);
}

void EventHandlerMock::handleEvent(SDL_Event event, ClientPlayer& player, bool &running, int& x, int& y) {
    bool must_update = false;
    double delta_alpha;
    std::pair<int, int> new_coordinates;
    //printf("Pos inicial del jugador: (%d, %d)\n", x, y);
    int proj_x = x;
    int proj_y = y;
    double new_angle;
    switch (event.type) {
        case SDL_KEYDOWN: {
            auto& key_event = (SDL_KeyboardEvent&) event;
            switch (key_event.keysym.sym) {
                case SDLK_a:
                    if (movementAllowed(proj_x, proj_y, M_PI/2, player, map)) {
                        must_update = true;
                        x = proj_x;
                        y = proj_y;
                    }
                    break;
                case SDLK_d:
                    if (movementAllowed(proj_x, proj_y, -M_PI/2, player, map)) {
                        must_update = true;
                        x = proj_x;
                        y = proj_y;
                    }
                    break;
                case SDLK_w:
                    if (movementAllowed(proj_x, proj_y, 0, player, map)) {
                        must_update = true;
                        x = proj_x;
                        y = proj_y;
                    }
                    break;
                case SDLK_s:
                    if (movementAllowed(proj_x, proj_y, M_PI, player, map)) {
                        must_update = true;
                        x = proj_x;
                        y = proj_y;
                    }
                    break;
                case SDLK_LEFT:
                    delta_alpha = 0.174533;
                    player.updateDirection(delta_alpha);
                    must_update = true;
                    break;
                case SDLK_RIGHT:
                    delta_alpha = -0.174533;
                    player.updateDirection(delta_alpha);
                    must_update = true;
                    break;
            }
            break;
        }
        case SDL_MOUSEMOTION:
            break;
        case SDL_QUIT:
            std::cout << "Quitting" << std::endl;
            running = false;
            break;
    }
    if (must_update) {
        std::pair<int, int> grid = map.calculateGrid(x, y);
        map.update(player, x, y);
        grid = map.calculateGrid(x, y);
        printf("El jugador se movio hacia: (%d, %d) y mira en direccion %f\n", x, y, player.getDirection());
    }
    else
        puts("El jugador no se movio ni giro\n");
}

void EventHandlerMock::calculateMovement(int& x, int& y, double alpha){
    int x_move = std::round(cos(alpha)*step_size);
    int y_move = std::round(sin(alpha)*step_size*-1);
    //printf("El jugador quiere moverse desde (%d, %d) ", x, y);
    x += x_move;
    y += y_move;
    //printf("hacia (%d, %d)\n", x, y);
    //printf("X PROYECTADO: %d\n", x);
    //printf("Y PROYECTADO: %d\n", y);
}

bool EventHandlerMock::movementAllowed(int& proj_x,
                                       int& proj_y,
                                       double angle_turn,
                                       ClientPlayer& player,
                                       MapMock& map) {
    double new_angle = player.projectDirection(angle_turn);
    //printf("Angulo proyectado: %f\n", new_angle);
    bool x_incr = (new_angle < M_PI / 2 || new_angle > 3 * M_PI / 2);
    bool y_incr = (new_angle > M_PI);
    calculateMovement(proj_x, proj_y, new_angle);
    return (map.movementAllowed(proj_x, proj_y, x_incr, y_incr));
}


