#ifndef DOOR_H
#define DOOR_H

#include "server/game/positionable.h"

class Door : public Positionable {
protected:
    bool is_locked;
public:
    Door(std::string type, int id, bool _is_locked);
    ~Door();

    Door(const Door& other);
    Door& operator=(const Door& other);

    bool openDoor() const;

    bool unlock();
};


#endif // DOOR_H