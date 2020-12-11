#ifndef TP_WOLFENSTEIN_SERVER_MAIN_H
#define TP_WOLFENSTEIN_SERVER_MAIN_H

#include <string>
#include "common/thread.h"
#include <atomic>

class Server {
private:
    std::string path;
    std::atomic<bool> playing;
public:
    Server(std::string path);

    ~Server();

};

#endif //TP_WOLFENSTEIN_SERVER_MAIN_H
