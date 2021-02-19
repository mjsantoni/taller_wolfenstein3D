#ifndef NETWORK_ACCEPTOR_H
#define NETWORK_ACCEPTOR_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdbool.h>
#include <string>
#include <vector>
#include "common/network_connection.h"

class NetworkAcceptor {
    private:
        int file_descriptor;

        /* Devuelve true o false segun si el controlador de red tiene un socket
        valido. */
        bool isValid() const;

        /* Inicializa la conexion obteniendo informacion a traves de getaddrinfo
        y almacenandola en addr_results que fue recibida. Para esto tambien recibe
        puerto y host. Levanta una excepcion propia del controlador de red
        en caso de error. */
        void start(struct addrinfo** addr_results, 
                   const char* host, const char* port);

        /* Recibe la estructura de informacion de la conexion.
        Inicializa el socket, lo asigna al servidor y pone al servidor
        en modo escucha ante potenciales conexiones. 
        Levanta una excepcion propia del controlador de red en caso de error.
        Esta funcion es utilizada exclusivamente por el servidor. */           
        void bindAndListen(struct addrinfo* addr_results);

    public:
        /* Constructor del socket aceptador de clientes. Recibe un puerto
        para conectarse. */
        explicit NetworkAcceptor(const char* port);

        /* Entabla la conexion entre el servidor y el cliente, utilizando el
        file descriptor de la conexion. Levanta una excepcion propia del 
        controlador de red en caso de error. */
        NetworkConnection acceptConnection();

        /* Desinicializa y cierra el socket asociado al controlador de red. */
        void closeSocket();

        /* Permite constructor y asignacion por movimiento. */
        NetworkAcceptor(NetworkAcceptor&& other);
        NetworkAcceptor& operator=(NetworkAcceptor&& other);

        /* Prohibe constructor y asignacion por copia. */
        NetworkAcceptor(const NetworkAcceptor& other) = delete;
        NetworkAcceptor& operator=(const NetworkAcceptor& other) = delete;

        /* Destructor por defecto del controlador de red. Cierra el socket
        si aun sigue siendo valido. */
        ~NetworkAcceptor();
};

#endif // NETWORK_ACCEPTOR_H
