#ifndef TP_WOLFENSTEIN_HIT_HANDLER_H
#define TP_WOLFENSTEIN_HIT_HANDLER_H
#include "server/game/hit.h"
#include "common/change.h"

class HitHandler {
private:
public:
    HitHandler();

    void processHit(Hit &hit_event, std::vector<Change> &changes, int players_alive);
    ~HitHandler();
};


#endif //TP_WOLFENSTEIN_HIT_HANDLER_H
