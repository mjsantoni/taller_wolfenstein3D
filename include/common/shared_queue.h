#ifndef TP_WOLFENSTEIN_SHARED_QUEUE_H
#define TP_WOLFENSTEIN_SHARED_QUEUE_H

#include <iostream>
#include <condition_variable>
#include <queue>
#include <thread>
#include <atomic>

template <class Object>
class SharedQueue {
private:
    std::mutex m;
    std::queue<Object> queue;

    // Este objeto solo sera devuelto cuando la cola este cerrada y vacia.
    Object empty_return;

public:
    explicit SharedQueue(Object _empty_return) :
                        empty_return(_empty_return) {}

    Object pop() {
        std::unique_lock<std::mutex> lock(m);
        if (queue.empty()) return empty_return;
        Object obj = queue.front();
        queue.pop();
        return obj;
    }

    void push(Object obj) {
        std::unique_lock<std::mutex> lock(m); //Creo que no va (mepa q si)
        queue.push(obj);
    }

    ~SharedQueue() {}
};


#endif //TP_WOLFENSTEIN_SHARED_QUEUE_H
