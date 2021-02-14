//
// Created by andy on 30/1/21.
//

#include "client/game/in_game_event_generator.h"

InGameEventGenerator::InGameEventGenerator(ClientPlayer &_player,
                                           InGameEventHandler &_event_handler,
                                           BlockingQueue<Event>& _event_queue,
                                           bool& _player_alive) :
        player(_player),
        event_handler(_event_handler),
        event_queue(_event_queue),
        player_alive(_player_alive) {
}

void InGameEventGenerator::generateInGameEvent(SDL_Event sdl_event) {
    if (!player_alive)
        return;
    Event event = Event(INVALID, player.getId(), 0);
    switch (sdl_event.type) {
        case SDL_KEYDOWN: {
            auto& key_event = (SDL_KeyboardEvent&) sdl_event;
            switch (key_event.keysym.sym) {
                case SDLK_a:
                    event = Event(MOVE_PLAYER, player.getId(), MOVE_LEFT);
                    break;
                case SDLK_d:
                    event = Event(MOVE_PLAYER, player.getId(), MOVE_RIGHT);
                    break;
                case SDLK_w:
                    event = Event(MOVE_PLAYER, player.getId(), MOVE_UP);
                    break;
                case SDLK_SPACE:
                    event = Event(SHOOT, player.getId(), 0);
                    break;
                case SDLK_s:
                    event = Event(MOVE_PLAYER, player.getId(), MOVE_DOWN);
                    break;
                    /*
                case SDLK_p:
                    event = Event(PLAYER_READY, player.getId(), 0);
                    break;
                     */
                case SDLK_LEFT:
                    event = Event(TURN_CAMERA, player.getId(), CAMERA_LEFT);
                    event_handler.handleCameraTurn(CAMERA_LEFT);
                    break;
                case SDLK_RIGHT:
                    event = Event(TURN_CAMERA, player.getId(), CAMERA_RIGHT);
                    event_handler.handleCameraTurn(CAMERA_RIGHT);
                    break;
                //case SDLK_ESCAPE:
                    // pausar juego
                case SDLK_e:
                    event = Event(OPEN_DOOR, player.getId(), 0);
                    break;
                case SDLK_f:
                    event = Event(PUSH_WALL, player.getId(), 0);
                    break;
                case SDLK_1:
                    std::cout << "Se envia evento de cambio de arma con valor " << 1 << std::endl;
                    event = Event(CHANGE_GUN, player.getId(), 1);
                    break;
                case SDLK_2:
                    std::cout << "Se envia evento de cambio de arma con valor " << 2 << std::endl;
                    event = Event(CHANGE_GUN, player.getId(), 2);
                    break;
                case SDLK_3:
                    std::cout << "Se envia evento de cambio de arma con valor " << 3 << std::endl;
                    event = Event(CHANGE_GUN, player.getId(), 3);
                    break;
                case SDLK_4:
                    std::cout << "Se envia evento de cambio de arma con valor " << 4 << std::endl;
                    event = Event(CHANGE_GUN, player.getId(), 4);
                    break;
                case SDLK_5:
                    std::cout << "Se envia evento de cambio de arma con valor " << 5 << std::endl;
                    event = Event(CHANGE_GUN, player.getId(), 5);
                    break;
            }
        }
            break;
        case SDL_MOUSEBUTTONDOWN: {
            auto& mouse_button_event = (SDL_MouseButtonEvent&) sdl_event;
            switch(mouse_button_event.button) {
                case SDL_BUTTON_LEFT:
                    event = Event(SHOOT, player.getId(), 0);
                    break;
            }
        }
    }
    if (event.isInvalid())
        return;
    //std::cout << "Se encola el evento " << event.getEventID() << std::endl;
    event_queue.push(event);
}
