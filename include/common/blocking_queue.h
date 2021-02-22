#ifndef TP_WOLFENSTEIN_BLOCKING_QUEUE_H
#define TP_WOLFENSTEIN_BLOCKING_QUEUE_H

#include <iostream>
#include <condition_variable>
#include <queue>
#include <thread>
#include <atomic>

template<class Object>
class BlockingQueue {
 private:
  std::atomic<bool> is_closed;
  std::mutex m;
  std::condition_variable cv;
  std::queue<Object> queue;

  // Este objeto solo sera devuelto cuando la cola este cerrada y vacia.
  Object empty_return;

 public:
  explicit BlockingQueue(Object empty_return) :
      is_closed(false), empty_return(empty_return) {}

  Object pop() {
    std::unique_lock<std::mutex> lock(m);
    while (queue.empty()) {
      if (is_closed) { // Devuelve el objeto especial empty_return
        return empty_return;
      }
      cv.wait(lock);
    }
    Object obj = queue.front();
    queue.pop();
    return obj;
  }

  void push(Object obj) {
    std::unique_lock<std::mutex> lock(m);
    queue.push(obj);
    cv.notify_all();
  }

  void close() {
    std::unique_lock<std::mutex> lock(m);
    is_closed = true;
    cv.notify_all();
  }

  ~BlockingQueue() {}
};

#endif //TP_WOLFENSTEIN_BLOCKING_QUEUE_H
