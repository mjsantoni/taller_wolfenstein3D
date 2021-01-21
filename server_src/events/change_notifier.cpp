#include "server/events/change_notifier.h"

ChangeNotifier::ChangeNotifier(BlockingQueue<Change>& _change_queue) :
                                change_queue(_change_queue),
                                running(true) {
}

void ChangeNotifier::run() {
/*
    while (running) {
        Change change = change_queue.pop(); // aca duermo mientras no hay nada
        if (change.isGlobal()) {
            for (clientupdater in all clientsupdater) {
                clientupdater.update(change) //es hacer un send del cambio --> sk.send(change.serialize())
            }
        }
        else {
            for (clientupdater in all clientsupdater) {
                if clientupdater.clientId == change.id() {
                    clientupdater.update(change);
                    break;
                }
            }
        }
    }
*/
}

void ChangeNotifier::stop() {
    running = false;
}

ChangeNotifier::~ChangeNotifier() {}
