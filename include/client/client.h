#ifndef TP_WOLFENSTEIN_CLIENT_H
#define TP_WOLFENSTEIN_CLIENT_H

#include <vector>
#include "common/thread.h"

class Client : public Thread {
private:
    std::vector<std::pair<int, int>>& walls;
    int map_width;
    int map_height;

public:
    Client(int width, int height, std::vector<std::pair<int,int>>& _walls);
    void run() override;
    ~Client();
};


#endif //TP_WOLFENSTEIN_CLIENT_H
