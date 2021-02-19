#ifndef TP_WOLFENSTEIN_SERVER_H
#define TP_WOLFENSTEIN_SERVER_H

#include <vector>
#include <atomic>
#include "server/events/game_handler.h"
#include "common/network_acceptor.h"
#include "common/network_error.h"
#include "common/network_connection.h"
#include "common/thread.h"


class Server : public Thread {
private:
    std::vector<GameHandler*> matches;
    NetworkAcceptor networkAcceptor;
    std::vector<std::string> maps;
    std::atomic<bool> accepting_connections;


public:
    Server(NetworkAcceptor socket);
    ~Server() override;

    void run() override;

    void stop();

    bool joinGame(int game_id, NetworkConnection socket);

    int createGame(int max_players, int bots, int game_duration, int map, int min_players_in_lobby);

    void killDead();

    std::vector<int> split(const std::string& bytes);
};

#endif //TP_WOLFENSTEIN_SERVER_H
