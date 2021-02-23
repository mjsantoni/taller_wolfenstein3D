#ifndef TP_WOLFENSTEIN_POSITIONABLE_H
#define TP_WOLFENSTEIN_POSITIONABLE_H

#include <string>

class Positionable {
 protected:
  std::string category;
  std::string type;
  int id;
  bool is_blocking;

 public:
  /* Constructor de la clase principal de elementos que existen en un mapa.
   * Recibe una categoria, un tipo, un id y si es bloqueante (pared, etc) o no.
   */
  Positionable(std::string _category, std::string _type, int _id, bool _is_blocking);

  std::string getCategory() const;
  std::string getType() const;
  int getId();
  bool isBlocking() const;
  ~Positionable() {}
  Positionable() {}

  Positionable(const Positionable& other);
  Positionable& operator=(const Positionable& other);
};

#endif //TP_WOLFENSTEIN_CLIENT_POSITIONABLE_H
