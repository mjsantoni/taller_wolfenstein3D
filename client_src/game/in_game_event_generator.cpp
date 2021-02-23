//
// Created by andy on 30/1/21.
//

#include "client/game/in_game_event_generator.h"

InGameEventGenerator::InGameEventGenerator(ClientPlayer& _player,
                                           InGameEventHandler& _event_handler,
                                           BlockingQueue<Event>& _event_queue,
                                           bool& _player_alive,
                                           bool& _game_running,
                                           bool& skip_stats) :
        player(_player),
        event_handler(_event_handler),
        event_queue(_event_queue),
        player_alive(_player_alive),
        game_running(_game_running),
        skip_stats(skip_stats) {
}

void InGameEventGenerator::generateInGameEvent(SDL_Event sdl_event) {
  if (!player_alive)
    return;
  Event event = Event(INVALID, player.getId(), 0);
  switch (sdl_event.type) {
    case SDL_KEYDOWN: {
      auto& key_event = (SDL_KeyboardEvent&) sdl_event;
      switch (key_event.keysym.sym) {
        case SDLK_a:event = Event(MOVE_PLAYER, player.getId(), MOVE_LEFT);
          break;
        case SDLK_d:event = Event(MOVE_PLAYER, player.getId(), MOVE_RIGHT);
          break;
        case SDLK_w:event = Event(MOVE_PLAYER, player.getId(), MOVE_UP);
          break;
        case SDLK_SPACE:event = Event(SHOOT, player.getId(), 0);
          break;
        case SDLK_s:event = Event(MOVE_PLAYER, player.getId(), MOVE_DOWN);
          break;
        case SDLK_LEFT:event = Event(TURN_CAMERA, player.getId(), CAMERA_LEFT);
          event_handler.handleCameraTurn(CAMERA_LEFT);
          break;
        case SDLK_RIGHT:event = Event(TURN_CAMERA, player.getId(), CAMERA_RIGHT);
          event_handler.handleCameraTurn(CAMERA_RIGHT);
          break;
        case SDLK_e:event = Event(OPEN_DOOR, player.getId(), 0);
          break;
        case SDLK_f:event = Event(PUSH_WALL, player.getId(), 0);
          break;
        case SDLK_1:
          event = Event(CHANGE_GUN, player.getId(), 1);
          break;
        case SDLK_2:
          event = Event(CHANGE_GUN, player.getId(), 2);
          break;
        case SDLK_3:
          event = Event(CHANGE_GUN, player.getId(), 3);
          break;
        case SDLK_4:
          event = Event(CHANGE_GUN, player.getId(), 4);
          break;
        case SDLK_5:
          event = Event(CHANGE_GUN, player.getId(), 5);
          break;
      }
    }
      break;
    case SDL_MOUSEBUTTONDOWN: {
      auto& mouse_button_event = (SDL_MouseButtonEvent&) sdl_event;
      switch (mouse_button_event.button) {
        case SDL_BUTTON_LEFT:event = Event(SHOOT, player.getId(), 0);
          break;
      }
    }
  }
  if (event.isInvalid())
    return;
  event_queue.push(event);
}

Event InGameEventGenerator::generateInGameEvent(int key) {
    switch (key) {
        case SDL_SCANCODE_A:
            return Event{MOVE_PLAYER, player.getId(), MOVE_LEFT};
        case SDL_SCANCODE_D:
            return Event{MOVE_PLAYER, player.getId(), MOVE_RIGHT};
        case SDL_SCANCODE_W:
            return Event{MOVE_PLAYER, player.getId(), MOVE_UP};
        case SDL_SCANCODE_SPACE:
            return Event{SHOOT, player.getId(), 0};
        case SDL_SCANCODE_S:
            return Event{MOVE_PLAYER, player.getId(), MOVE_DOWN};
        case SDL_SCANCODE_LEFT:
            event_handler.handleCameraTurn(CAMERA_LEFT);
            return Event{TURN_CAMERA, player.getId(), CAMERA_LEFT};
        case SDL_SCANCODE_RIGHT:
            event_handler.handleCameraTurn(CAMERA_RIGHT);
            return Event{TURN_CAMERA, player.getId(), CAMERA_RIGHT};
        case SDL_SCANCODE_E:
            return Event{OPEN_DOOR, player.getId(), 0};
        case SDL_SCANCODE_F:
            return Event{PUSH_WALL, player.getId(), 0};
        case SDL_SCANCODE_1:
            return Event{CHANGE_GUN, player.getId(), 1};
        case SDL_SCANCODE_2:
            return Event{CHANGE_GUN, player.getId(), 2};
        case SDL_SCANCODE_3:
            return Event{CHANGE_GUN, player.getId(), 3};
        case SDL_SCANCODE_4:
            return Event{CHANGE_GUN, player.getId(), 4};
        case SDL_SCANCODE_5:
            return Event{CHANGE_GUN, player.getId(), 5};
        default:
            return Event{INVALID, player.getId(), 0};
    }
}
/*
void InGameEventGenerator::generateInGameEvents() {
  SDL_Event event;
  if (SDL_PollEvent(&event) == 0) {
    return;
  }
  switch (event.type) {
    case SDL_KEYDOWN: {
      generateInGameEvent(event);
      break;
    }
    case SDL_MOUSEBUTTONDOWN:generateInGameEvent(event);
      break;
    case SDL_QUIT:game_running = false;
      skip_stats = true;
      puts("Saliendo");
      return;
  }
}
*/
void InGameEventGenerator::generateInGameEvents() {
    if (!player_alive)
        return;
    SDL_Event event;
    if (SDL_PollEvent(&event) == 0) {
        return;
    }
    std::vector<Event> events;
    processMouseEvent(event, events);
    const Uint8* keyboard_state =  SDL_GetKeyboardState(nullptr);

    for (auto& key : important_keys) {
        if (keyboard_state[key]) {
            Event each_event = generateInGameEvent(key);
            if (!each_event.isInvalid())
                events.push_back(each_event);
        }
    }
    for (auto& each_event : events) {
        event_queue.push(each_event);
    }
}

void InGameEventGenerator::processMouseEvent(SDL_Event& event,
                                             std::vector<Event>& events) {
    if (event.type != SDL_MOUSEBUTTONDOWN)
        return;
    auto& mouse_button_event = (SDL_MouseButtonEvent&) event;
    if (mouse_button_event.button != SDL_BUTTON_LEFT)
        return;
    Event game_event(SHOOT, player.getId(), 0);
    events.push_back(game_event);
}
