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
        event_handler(change_queue),
        event_generator(player, event_handler, event_queue, game_started),
        change_processor(player, change_queue, game_started, player_ready){
    //
}

void ClientGameHandler::start() {
    change_processor.start();
    while (!player_ready) {}
    event_generator.generateReadyEvent();
    while (!game_started) {}
    std::cout << "Se inicia la partida" << std::endl;
    SDL_Event event;
    while (running) {
        if (SDL_PollEvent(&event) == 0) continue;
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
            default:
                break;
        }
        //sleep(10);
    }
    std::cout << "Frena change processor" << std::endl;
    change_processor.stop();
    change_processor.join();
}

bool ClientGameHandler::isRunning() {
    return running;
}