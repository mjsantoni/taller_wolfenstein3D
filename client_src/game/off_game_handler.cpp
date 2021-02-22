#include <SDL_events.h>
#include <SDL_timer.h>
#include "client/game/off_game_handler.h"
#include "client_routes.h"

OffGameHandler::OffGameHandler(GameScreen& _screen,
                               ClientPlayer& player,
                               ClientMap& _map,
                               SharedQueue<Change>& change_queue,
                               BlockingQueue<Event>& event_queue) :
    screen(_screen),
    map(_map),
    change_processor(_map, player, change_queue,
                     game_started, player_ready),
    event_generator(event_queue, player) {
}

void OffGameHandler::displayMenus(const std::string& map_name) {
  //event_handler.defineKeyScreenAreas(screen.getKeyScreenAreas());
  //audio_manager.playSong();
  displayIntro();
  initializeMap(map_name);
  displayLoadingScreen();
  //audio_manager.stopSong();
}

void OffGameHandler::displayIntro() {
  screen.displayIntro();
  while (true) {
    SDL_Event event;
    SDL_WaitEvent(&event);
    if (event.type == SDL_KEYDOWN)
      break;
  }
}

void OffGameHandler::displayLoadingScreen() {
  screen.displayLoadingScreen(true);
  SDL_Event event;
  while (!player_ready || !game_started) {
    usleep(30000);
    change_processor.processOffGameChanges();
    if (SDL_PollEvent(&event) == 0)
      continue;
    bool player_pressed_p = event_handler.handleLoadingScreenEvent(event);
    if (player_pressed_p) {
      event_generator.generateReadyEventIfNecessary();
      screen.displayLoadingScreen(false);
    }
    //std::cout << "Player ready: " << player_ready << std::endl;
    //std::cout << "Game started: " << game_started << std::endl;
  }
  std::cout << "TERMINA LA INTRO\n";
}

void OffGameHandler::initializeMap(const std::string& map_name) {
  std::string map_path = MAPS_PATH_FOLDER + map_name;
  MapParser map_parser(map_path);
  ClientMapGenerator::create(map, map_parser);
}

