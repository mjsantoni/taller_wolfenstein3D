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

public:
    explicit SharedQueue() {}

    Object pop() {
        std::unique_lock<std::mutex> lock(m);
        Object obj = queue.front();
        queue.pop();
        return obj;
    }

    void push(Object obj) {
        //std::unique_lock<std::mutex> lock(m); //Creo que no va
        queue.push(obj);
    }

    ~SharedQueue() {}
};


#endif //TP_WOLFENSTEIN_SHARED_QUEUE_H
