//
// Created by andy on 10/12/20.
//

#ifndef TP_WOLFENSTEIN_CLIENT_PARSER_H
#define TP_WOLFENSTEIN_CLIENT_PARSER_H

#include <client/client_map.h>

class ClientParser {
private:
    std::vector<std::pair<int, int>> createWalls(int width, int height);
    std::vector<int> createTypes(int width, int height);
public:
    ClientMap parseInfoFromServer();
};


#endif //TP_WOLFENSTEIN_CLIENT_PARSER_H
