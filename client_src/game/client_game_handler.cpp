//
// Created by andy on 27/11/20.
//

#include <SDL_events.h>
#include <iostream>
#include <SDL_timer.h>
#include <client/game/client_game_handler.h>
#include <client/communication/server_updater.h>


ClientGameHandler::ClientGameHandler(SharedQueue<Change>& change_queue,
                                     BlockingQueue<Event>& event_queue) :
        running(true),
        game_started(false),
        player_ready(false),
        screen(960, 600, map, player),
        event_handler(change_queue),
        event_generator(player, event_handler, event_queue, game_started),
        change_processor(screen, map, player, change_queue, audio_manager),
        off_game_change_processor(game_started, player_ready, map, player, change_queue),
        intro_handler(screen, map, map_path, off_game_change_processor,
                      game_started, player_ready) {
    //
}

void ClientGameHandler::start() {
    //change_processor.start();
    initializePlayer();
    intro_handler.displayMenus();
    //while (!player_ready) {}
    event_generator.generateReadyEvent();
    //while (!game_started) {}
    //screen.clearWindow();
    screen.render(std::vector<int>{1, 1, 1, 1});
    std::cout << "Se inicia la partida" << std::endl;
    SDL_Event event;
    while (running) {
        if (SDL_PollEvent(&event) == 0) {
            usleep(70000);
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
        change_processor.processInGameChanges();
        usleep(33000);
    }
    std::cout << "Frena change processor" << std::endl;
}

bool ClientGameHandler::isRunning() {
    return running;
}

void ClientGameHandler::initializePlayer() {
    player_initializer.initializePlayer(player);
}