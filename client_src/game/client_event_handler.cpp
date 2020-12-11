//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include "client/client_event_handler.h"

ClientEventHandler::ClientEventHandler(Map& _map) : map(_map) {
}

void ClientEventHandler::handleEvent(SDL_Event event, Player& player, bool &running, int& x, int& y) {
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
                    delta_alpha = M_PI/4;
                    player.updateDirection(delta_alpha);
                    must_update = true;
                    break;
                case SDLK_RIGHT:
                    delta_alpha = -M_PI/4;
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

void ClientEventHandler::handleMouseEvent(SDL_Event event,
                                    Player &player,
                                    SdlWindow& window) {
    auto& mouse_event = (SDL_MouseMotionEvent&) event;
    int x_position = mouse_event.x;
    if (x_position == 0)
        player.updateDirection(-M_PI/8);
    if (x_position == window.getWidth()-1)
        player.updateDirection(M_PI/8);
    //player.updateDirection(alpha_offset);
    mouse_position_x = mouse_event.x;
}

void ClientEventHandler::getMousePosition() {
    SDL_GetMouseState(&mouse_position_x, nullptr);
}

void ClientEventHandler::calculateMovement(int& x, int& y, double alpha){
    double delta_alpha;
    int x_factor;
    int y_factor;
    if (alpha <= M_PI/2) {
        delta_alpha = alpha;
        x_factor = 1;
        y_factor = -1;
    } else if (alpha <= M_PI) {
        delta_alpha = M_PI - alpha;
        x_factor = -1;
        y_factor = -1;
    } else if (alpha <= 3*M_PI/2) {
        delta_alpha = alpha - M_PI;
        x_factor = -1;
        y_factor = 1;
    } else {
        delta_alpha = 2*M_PI-alpha;
        x_factor = 1;
        y_factor = 1;
    }
    int delta_x = (int) (step_size*cos(delta_alpha)*x_factor);
    int delta_y = (int) (step_size*sin(delta_alpha)*y_factor);
    printf("El jugador quiere moverse desde (%d, %d) ", x, y);
    x += delta_x;
    y += delta_y;
    printf("hacia (%d, %d)\n", x, y);
    //printf("X PROYECTADO: %d\n", x);
    //printf("Y PROYECTADO: %d\n", y);
}

bool ClientEventHandler::movementAllowed(int& proj_x,
                                   int& proj_y,
                                   double angle_turn,
                                   Player& player,
                                   Map& map) {
    double new_angle = player.projectDirection(angle_turn);
    printf("Angulo proyectadO: %f\n", new_angle);
    bool x_incr = (new_angle < M_PI / 2 || new_angle > 3 * M_PI / 2);
    bool y_incr = (new_angle > M_PI);
    printf("x incr: %d\n", x_incr);
    printf("y incr: %d\n", y_incr);
    calculateMovement(proj_x, proj_y, new_angle);
    return (map.movementAllowed(proj_x, proj_y, x_incr, y_incr));
}

void ClientEventHandler::putPlayerAt(std::string player_name,
                                     std::pair<int, int> position) {
    map.putPlayerAt(player_name, position);
}

