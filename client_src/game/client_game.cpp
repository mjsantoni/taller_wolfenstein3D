//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include <SDL_timer.h>
#include <client/game/client_game.h>
#include <client/communication/server_updater.h>

#define TICK_DURATION 0.05


ClientGame::ClientGame(SharedQueue<Change>& change_queue,
                       BlockingQueue<Event>& event_queue) :
        game_running(true),
        game_started(false),
        player_ready(false),
        screen(1024, 768, map, player, player_alive),
        event_handler(change_queue),
        event_generator(player, event_handler, event_queue, player_alive,
                        game_running),
        change_processor(screen, map, player, change_queue, audio_manager,
            statistics_manager, player_alive, game_running),
        off_game_handler(screen, player, map, change_queue, event_queue) {
    audio_manager.playGameSong();
}

void ClientGame::startGame(const std::string& map_name) {
    initializePlayer();
    off_game_handler.displayMenus(map_name);
    screen.render(true);
    std::cout << "Se inicia la partida" << std::endl;
    audio_manager.setMusicVolume(20);
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
    game_running = false;
}

void ClientGame::processGame() {
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
            break;
        case 0:
            screen.displayTimeOverScreen();
            break;
        case 1:
            audio_manager.playVictorySong();
            screen.displayVictoryScreen();
            break;
        default:
            break;
    }
    sleep(2);
}

void ClientGame::displayStatistics() {
    audio_manager.stopGameSong();
    if (event_generator.playerQuitted())
        return;
    int game_result = processGameResult();
    displayResultScreen(game_result);
    while (true) {
        screen.displayStatistics(statistics_manager.getStatistics());
        SDL_Event event;
        if (SDL_PollEvent(&event) == 0) {
            continue;
        }
        if (event.type == SDL_KEYDOWN || event.type == SDL_QUIT)
            return;
    }
}

ClientGame::~ClientGame() {
    audio_manager.stopGameSong();
}
