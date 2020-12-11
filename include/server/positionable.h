#ifndef TP_WOLFENSTEIN_POSITIONABLE_H
#define TP_WOLFENSTEIN_POSITIONABLE_H

#include <string>

class Positionable {
public:
    Positionable(std::string type, bool _is_blocking);
    std::string getType();
    bool isBlocking();
    ~Positionable() {}

protected:
    std::string type;
    int id;
    bool is_blocking;
};


#endif //TP_WOLFENSTEIN_CLIENT_POSITIONABLE_H
