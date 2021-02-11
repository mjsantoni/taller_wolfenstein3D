#ifndef NETWORK_CONNECTION_H
#define NETWORK_CONNECTION_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdbool.h>
#include <string>

class NetworkConnection {
public:
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

    /* Recibe la estructura de informacion de la conexion. Itera por todas las
    posibles conexiones hasta lograr conectar al servidor. Levanta una excepcion 
    propia del controlador de red en caso de error.
    Esta funcion es utilizada exclusivamente por el cliente. */
    void connectTo(struct addrinfo* addr_results);

public:
    /* Constructor del controlador de red del nuevo cliente
    a conectarse al servidor. Recibe el file descriptor asociado a la
    conexion. */
    explicit NetworkConnection(int fd);
   
    /* Constructor del controlador de red del cliente base.
    Recibe host y puerto para conectarse. */
    NetworkConnection(const char* host, const char* port);

    /* Recibe un mensaje. Envia el mensaje al servidor.
    Levanta una excepcion propia del controlador de red en caso de error
    y devuelve 0 al enviar todos los bytes respectivos. */
    //void sendMsg(const std::string& message);

    /* Funcion base de envio de mensajes. Recibe un mensaje y su 
    longitud. Envia el mensaje via socket. */
    //void sendMsg(const char* message, size_t message_length);
    void send_size(uint32_t len);
    int send_msg(std::string msg);

    /* Recibe un mensaje y luego lo devuelve como string.
    De haber algun error levanta una excepcion propia
    del controlador de red. */
    //std::string recvMsg();

    /* Funcion base de recepcion de mensajes. Recibe un buffer y su
    longitud maxima. Devuelve la cantidad de bytes recibidos. */
    //size_t recvMsg(char* message, size_t buff_length);
    uint32_t recv_size();
    int recv_msg(std::string &buffer);

    /* Cierra el canal de envio de datos del socket. */
    void shutdownAll();
    void shutdownSend();
    void shutdownRecv();

    /* Desinicializa y cierra el socket asociado al controlador de red. */
    void closeSocket();

    /* Permite constructor y asignacion por movimiento. */
    NetworkConnection(NetworkConnection&& other);
    NetworkConnection& operator=(NetworkConnection&& other);

    /* Prohibe constructor y asignacion por copia. */
    NetworkConnection(const NetworkConnection& other) = delete;
    NetworkConnection& operator=(const NetworkConnection& other) = delete;

    /* Destructor por defecto del controlador de red. Cierra el socket
    si aun sigue siendo valido. */
    ~NetworkConnection();
};
#endif // NETWORK_CONNECTION_H
