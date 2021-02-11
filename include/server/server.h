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
    int total_matches = 0;


public:
    Server(NetworkAcceptor socket);
    ~Server() override;

    void run() override;

    void stop();

    bool joinGame(int game_id, NetworkConnection socket);

    int createGame(int players, int bots, int game_duration,
                   int map);

    void killDead();
};


#endif //TP_WOLFENSTEIN_SERVER_H
