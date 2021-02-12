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
        running(true),
        game_started(false),
        player_ready(false),
        screen(600, 750, map, player),
        event_handler(change_queue),
        event_generator(player, event_handler, event_queue),
        change_processor(screen, map, player, change_queue, audio_manager),
        off_game_handler(screen, player, map, change_queue, event_queue) {
    //
}

void ClientGame::startGame() {
    initializePlayer();
    off_game_handler.displayMenus();
    screen.render(std::vector<int>{1, 1, 1, 1});
    std::cout << "Se inicia la partida" << std::endl;
    SDL_Event event;

    while (running) {
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
    return running;
}

void ClientGame::initializePlayer() {
    player_initializer.initializePlayer(player);
}
