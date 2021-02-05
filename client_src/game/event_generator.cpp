//
// Created by andy on 30/1/21.
//

#include "client/game/event_generator.h"

void EventGenerator::stop() {
    is_running = false;
}

void EventGenerator::generateInGameEvent(SDL_Event sdl_event) {
    if (!is_running)
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
                case SDLK_s:
                    event = Event(MOVE_PLAYER, player.getId(), MOVE_DOWN);
                    break;
                case SDLK_p:
                    event = Event(PLAYER_READY, player.getId(), 0);
                    break;
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
                    event_handler.handleWeaponChange(1);
                    break;
                case SDLK_2:
                    event_handler.handleWeaponChange(2);
                    break;
                case SDLK_3:
                    event_handler.handleWeaponChange(3);
                    break;
                case SDLK_4:
                    event_handler.handleWeaponChange(4);
                    break;
                case SDLK_5:
                    event_handler.handleWeaponChange(5);
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
    server_updater.update(event);
}

EventGenerator::EventGenerator(ClientPlayer &_player,
                               ClientEventHandler &_event_handler,
                               ServerUpdater &_server_updater) :
                               player(_player),
                               event_handler(_event_handler),
                               server_updater(_server_updater){
}

