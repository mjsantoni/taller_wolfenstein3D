#include "server/game/game_handler.h"

GameHandler::GameHandler(std::string path) : game(path, path),
                                             ef(eventQueue),
                                             ep(game,eq) {}

void GameHandler::run() {
    //ef.start();
    //ep.start();
    //proccess();
}
/*
void GameHandler::proccess() {
    while (game.isNotOver()) {
        while (eventQueue.isNotEmpty()) {
            Event event = eventQueue.pop();
            std::vector<Change> changes = ep.proccess(event);
            for (auto& change : changes) {
                BloquinChnageQueue.push(change)
            }
        }
        //game.passTime();
        sleep(20);
    }
    stop();
}
*/

/*
Hereda de Thread
Notifier::run() {
    while bloqkingquueueinsotemptyu() {
        Change = BlockingQueue<Change>.pop(); // aca duermo mientras no hay nada
        if change.isGlobal() {
            for (clientupdater in all clientsupdater) {
                clientupdater.update(change) //es hacer un send del cambio --> sk.send(change.serialize())
            }
        }
        else {
            for (clientupdater in all clientsupdater) {
                if clientupdater.clientId == change.id(){
                    clientupdater.update(change);
                    break;
                }
            }
        }
    }
}
 */