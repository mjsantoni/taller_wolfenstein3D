//
// Created by andy on 5/2/21.
//

#ifndef TP_WOLFENSTEIN_CHANGE_FACTORY_H
#define TP_WOLFENSTEIN_CHANGE_FACTORY_H

#include <common/shared_queue.h>
#include <common/change.h>

class ChangeFactory {
 private:
  SharedQueue<Change>& change_queue;
  // Es de Event* o Event?

 public:
  explicit ChangeFactory(SharedQueue<Change>& _event_queue);
  Change createFromBytes(char* bytes);
};

#endif //TP_WOLFENSTEIN_CHANGE_FACTORY_H
