#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
 private:
  std::thread thread;

 public:
  /* Constructor. */
  Thread();

  /* Inicializa el thread. */
  void start();

  /* Pone en espera al thread hasta que finalice su ejecucion. */
  void join();

  /* Metodo que implementa la clase que utiliza el
  thread para funcionar. */
  virtual void run() = 0;

  /* Destructor. */
  virtual ~Thread();

  /* Prohibe construccion y asignacion por copia. */
  Thread(const Thread&) = delete;
  Thread& operator=(const Thread&) = delete;

  /* Permite construccion y asignacion por movimiento. */
  Thread(Thread&& other);
  Thread& operator=(Thread&& other);
};

#endif // THREAD_H
