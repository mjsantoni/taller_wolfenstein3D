#ifndef DOOR_H
#define DOOR_H

#include "positionable.h"

class Door : public Positionable {
 protected:

 public:
  Door(std::string type, int id);

  ~Door();
};

#endif // DOOR_H
