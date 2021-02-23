//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include <client/game/client_game.h>
#include <client/communication/server_updater.h>

#define TICK_DURATION_SC 0.03
#define TICK_DURATION_MS 30000
#define IN_GAME_VOLUME 20

ClientGame::ClientGame(int screen_width,
                       int screen_height,
                       SharedQueue<Change>& change_queue,
                       BlockingQueue<Event>& event_queue) :
    game_running(true),
    game_started(false),
    player_ready(false),
    screen(screen_width, screen_height, map, player, player_alive),
    event_handler(change_queue),
    event_generator(player, event_handler, event_queue, player_alive,
                    game_running, skip_stats),
    change_processor(screen, map, player, change_queue, audio_manager,
                    statistics_manager, player_alive, game_running, skip_stats),
    off_game_handler(screen, player, map, change_queue, event_queue,
                     skip_stats, game_running) {
  audio_manager.playGameSong();
}

void ClientGame::startGame(const std::string& map_name) {
  initializePlayer();
  off_game_handler.displayMenus(map_name);
  if (!game_running)
     return;
  screen.render(true);
  audio_manager.setMusicVolume(IN_GAME_VOLUME);
  processGame();
}

void ClientGame::initializePlayer() {
  player_initializer.initializePlayer(player);
}

void ClientGame::displayConnectionErrorScreen() {
  screen.displayNetworkConnectionErrorScreen();
  game_running = false;
}

void ClientGame::processGame() {
  while (game_running) {
    auto initial_time = std::chrono::system_clock::now();
    change_processor.processInGameChanges();
    event_generator.generateInGameEvents();
    auto final_time = std::chrono::system_clock::now();
    std::chrono::duration<double> delta_t = final_time - initial_time;
    double reminder = TICK_DURATION_SC - delta_t.count();
    reminder = (reminder > 0) ? reminder : 0;
    usleep(reminder);
  }
}

int ClientGame::processGameResult() {
  if (!player_alive)
    return -1;
  if (map.getEnemiesAlive() > 0)
    return 0;
  return 1;
}

void ClientGame::displayResultScreen(int game_result) {
  switch (game_result) {
    case -1:
        audio_manager.playDefeatSong();
        screen.displayDefeatScreen();
        sleep(4);
      break;
    case 0:
        audio_manager.playTimeUpSong();
        screen.displayTimeOverScreen();
        sleep(2);
      break;
    case 1:
        audio_manager.playVictorySong();
        screen.displayVictoryScreen();
        sleep(4);
      break;
    default:break;
  }

}

void ClientGame::displayStatistics() {
  audio_manager.stopGameSong();
  if (skip_stats)
    return;
  int game_result = processGameResult();
  displayResultScreen(game_result);
  while (true) {
    usleep(TICK_DURATION_MS);
    screen.displayStatistics(statistics_manager.getStatistics());
    SDL_Event event;
    if (SDL_PollEvent(&event) == 0) {
      continue;
    }
    if (event.type == SDL_QUIT)
      return;
  }
}
