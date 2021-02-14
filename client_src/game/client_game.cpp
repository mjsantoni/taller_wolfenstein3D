//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include <SDL_timer.h>
#include <client/game/client_game.h>
#include <client/communication/server_updater.h>


ClientGame::ClientGame(SharedQueue<Change>& change_queue,
                       BlockingQueue<Event>& event_queue) :
        game_running(true),
        game_started(false),
        player_ready(false),
        screen(960, 600, map, player, player_alive),
        event_handler(change_queue),
        event_generator(player, event_handler, event_queue, player_alive),
        change_processor(screen, map, player, change_queue, audio_manager,
                         player_alive, game_running),
        off_game_handler(screen, player, map, change_queue, event_queue) {
    //
}

void ClientGame::startGame() {
    initializePlayer();
    off_game_handler.displayMenus();
    screen.render(std::vector<int>{1, 1, 1, 1});
    std::cout << "Se inicia la partida" << std::endl;
    SDL_Event event;
    while (game_running) {
        //std::cout << "inicio ciclo de juego\n";
        usleep(33000);
        change_processor.processInGameChanges();
        if (SDL_PollEvent(&event) == 0) {
            continue;
        }
        switch(event.type) {
            case SDL_KEYDOWN: {
                event_generator.generateInGameEvent(event);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
                event_generator.generateInGameEvent(event);
                break;
            case SDL_QUIT:
                puts("Saliendo");
                return;
        }
    }
    std::cout << "Frena change processor" << std::endl;
}

bool ClientGame::isRunning() {
    return game_running;
}

void ClientGame::initializePlayer() {
    player_initializer.initializePlayer(player);
}
