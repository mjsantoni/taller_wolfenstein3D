#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "common/network_error.h"
#include "common/network_acceptor.h"

#define MAX_CONNECTIONS 10

NetworkAcceptor::NetworkAcceptor(const char* port) {
  struct addrinfo* info;
  start(&info, NULL, port);

  try {
    bindAndListen(info);
  } catch (NetworkError& e) {
    freeaddrinfo(info);
    throw;
  }
}

void NetworkAcceptor::start(struct addrinfo** addr_results,
                            const char* host, const char* port) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  int gai_output;
  if ((gai_output = getaddrinfo(host, port, &hints, addr_results)) != 0) {
    throw NetworkError("Error executing getaddrinfo: %s\n",
                       gai_strerror(gai_output));
  }
}

void NetworkAcceptor::bindAndListen(struct addrinfo* addr_results) {
  struct addrinfo* addr_copy = addr_results;
  int new_socket = 0;
  const char* error_msg = "";

  for (; addr_copy != NULL; addr_copy = addr_copy->ai_next) {
    // Initialize socket
    new_socket = socket(addr_copy->ai_family,
                        addr_copy->ai_socktype,
                        addr_copy->ai_protocol);
    if (new_socket == -1) {
      error_msg = "Error initializing socket: ";
      continue;
    }
    // Allows reusing same port with no timeout
    int sockopt_int = 1;
    if (setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR,
                   &sockopt_int, sizeof(sockopt_int)) == -1) {
      error_msg = "Error allowing reuse of same port: ";
      close(new_socket);
      continue;
    }
    // Binds socket to server
    if (bind(new_socket, addr_copy->ai_addr,
             addr_copy->ai_addrlen) == -1) {
      error_msg = "Error binding: ";
      close(new_socket);
      continue;
    }
    // Puts server on listening mode for a client connection
    if (listen(new_socket, MAX_CONNECTIONS) == -1) {
      error_msg = "Error listening: ";
      close(new_socket);
      continue;
    }
    break;
  }
  this->file_descriptor = new_socket;

  if (addr_copy == NULL) {
    throw NetworkError("%s%s\n", error_msg, strerror(errno));
  }
  freeaddrinfo(addr_results);
}

NetworkConnection NetworkAcceptor::acceptConnection() {
  int new_socket = 0;

  new_socket = accept(this->file_descriptor, NULL, NULL);
  if (new_socket == -1) {
    throw NetworkError("Error accepting connection: %s\n",
                       strerror(errno));
  }
  return NetworkConnection(new_socket);
}

bool NetworkAcceptor::isValid() const {
  return this->file_descriptor != -1;
}

void NetworkAcceptor::closeSocket() {
  shutdown(this->file_descriptor, SHUT_RDWR);
  if (isValid()) close(this->file_descriptor);
}

NetworkAcceptor::NetworkAcceptor(NetworkAcceptor&& other) {
  this->file_descriptor = other.file_descriptor;
  other.file_descriptor = -1;
}
NetworkAcceptor& NetworkAcceptor::operator=(NetworkAcceptor&& other) {
  this->file_descriptor = other.file_descriptor;
  other.file_descriptor = -1;
  return *this;
}

NetworkAcceptor::~NetworkAcceptor() {
  if (isValid()) {
    shutdown(this->file_descriptor, SHUT_RDWR);
    close(this->file_descriptor);
    this->file_descriptor = -1;
  }
}
