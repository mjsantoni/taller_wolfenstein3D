#include "server/matches.h"

Matches::Matches() {}
Matches::~Matches() {}

void Matches::addNewMatch(GameHandler* match) {
    std::unique_lock<std::mutex> lock(m);
    matches.push_back(match);
}

int Matches::getSize() {
    std::unique_lock<std::mutex> lock(m);
    return matches.size();
}

bool Matches::canJoinPlayer(int id) {
    std::unique_lock<std::mutex> lock(m);
    return matches[id]->canJoinPlayer();
}

void Matches::addNewPlayer(int id, NetworkConnection skt) {
    std::unique_lock<std::mutex> lock(m);
    matches[id]->addNewPlayer(std::move(skt));
}

void Matches::sendGames(NetworkConnection& skt) {
    std::unique_lock<std::mutex> lock(m);
    for (auto& game : matches) {
        if (game->canJoinPlayer()) {
            skt.send_msg(game->getInformation());
        }
    }
    skt.send_msg(SUCCESS);
}

static bool is_null(GameHandler* gh) { return !gh; }

void Matches::killDead() {
    std::unique_lock<std::mutex> lock(m);
    int i = 0;
    for (auto& game : matches) {
        if (game->ended()) {
            game->join();
            delete game;
            matches[i] = nullptr;
        }
        i++;
    }
    matches.erase(std::remove_if(matches.begin(), matches.end(), is_null),
                  matches.end());
}

void Matches::stopGames() {
    std::unique_lock<std::mutex> lock(m);
    for (auto& th_game : matches) {
        th_game->stop();
        th_game->join();
        delete th_game;
    }
}