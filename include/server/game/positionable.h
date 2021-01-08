#ifndef TP_WOLFENSTEIN_POSITIONABLE_H
#define TP_WOLFENSTEIN_POSITIONABLE_H

#include <string>

class Positionable {
public:
    Positionable(std::string _category, std::string _type, int _id, bool _is_blocking);

    std::string getCategory();
    std::string getType();
    int getId();
    bool isBlocking();
    ~Positionable() {}
    Positionable() {}
    Positionable(const Positionable& other);
    Positionable& operator=(const Positionable& other);

protected:
    std::string category;
    std::string type;
    int id;
    bool is_blocking;
};


#endif //TP_WOLFENSTEIN_CLIENT_POSITIONABLE_H
