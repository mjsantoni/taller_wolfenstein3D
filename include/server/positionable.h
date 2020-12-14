#ifndef TP_WOLFENSTEIN_POSITIONABLE_H
#define TP_WOLFENSTEIN_POSITIONABLE_H

#include <string>

class Positionable {
public:
    Positionable(std::string _type, std::string _id, bool _is_blocking);
    std::string getType();
    std::string getId();
    bool isBlocking();
    ~Positionable() {}
    virtual void foo() {}

protected:
    std::string type;
    std::string id;
    bool is_blocking;
};


#endif //TP_WOLFENSTEIN_CLIENT_POSITIONABLE_H
