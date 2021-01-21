#ifndef TP_WOLFENSTEIN_CHANGE_NOTIFIER_H
#define TP_WOLFENSTEIN_CHANGE_NOTIFIER_H

#include "common/thread.h"
#include "common/blocking_queue.h"
#include "common/change.h"
#include <atomic>
#include <vector>
#include "server/events/client_updater.h"

class ChangeNotifier : public Thread {
private:
    BlockingQueue<Change>& change_queue;
    std::atomic<bool> running;
    std::vector<ClientUpdater*> client_updaters;

public:
    explicit ChangeNotifier(BlockingQueue<Change>& _change_queue);
    ~ChangeNotifier();

    void run() override;

    void stop();
};


#endif //TP_WOLFENSTEIN_CHANGE_NOTIFIER_H
