//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include <SDL_timer.h>
#include <client/game/client_game.h>
#include <client/communication/server_updater.h>

#define TICK_DURATION 0.03


ClientGame::ClientGame(SharedQueue<Change>& change_queue,
                       BlockingQueue<Event>& event_queue) :
        game_running(true),
        game_started(false),
        player_ready(false),
        screen(960, 600, map, player, player_alive),
        event_handler(change_queue),
        event_generator(player, event_handler, event_queue, player_alive),
        change_processor(screen, map, player, change_queue, audio_manager,
                         statistics_manager, player_alive, game_running),
        off_game_handler(screen, player, map, change_queue, event_queue) {
    //
}

void ClientGame::startGame() {
    initializePlayer();
    off_game_handler.displayMenus();
    screen.render(std::vector<int>{1, 1, 1, 1});
    std::cout << "Se inicia la partida" << std::endl;
    processGame();
    std::cout << "Frena change processor" << std::endl;
}

bool ClientGame::isRunning() {
    return game_running;
}

void ClientGame::initializePlayer() {
    player_initializer.initializePlayer(player);
}

void ClientGame::displayConnectionErrorScreen(std::string message) {
    screen.displayNetworkConnectionErrorScreen(std::move(message));
}

void ClientGame::processGame() {
    SDL_Event event;
    while (game_running) {
        auto initial_time = std::chrono::system_clock::now();
        change_processor.processInGameChanges();
        event_generator.generateInGameEvents();
        auto final_time = std::chrono::system_clock::now();
        std::chrono::duration<double> delta_t = final_time - initial_time;
        double reminder = TICK_DURATION - delta_t.count();
        reminder = (reminder > 0) ? reminder : 0;
        usleep(reminder);
    }
}

void ClientGame::displayStatistics() {
    screen.displayStatistics(statistics_manager.getStatistics());
}
