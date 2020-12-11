#ifndef TP_WOLFENSTEIN_POSITIONABLE_H
#define TP_WOLFENSTEIN_POSITIONABLE_H

#include <string>

class Positionable {
public:
    Positionable(std::string type, bool _is_obstructive);
    std::string getType();
    ~Positionable() {}

protected:
    std::string type;
    int id;
    bool is_obstructive;
};


#endif //TP_WOLFENSTEIN_CLIENT_POSITIONABLE_H
