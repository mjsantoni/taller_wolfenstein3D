#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

#include "common/network_connection.h"
#include "common/network_error.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <sstream>

#define BUFFER_LENGTH 64

NetworkConnection::NetworkConnection(int fd) : file_descriptor(fd) {}

NetworkConnection::NetworkConnection(const char* host, const char* port) {
    struct addrinfo* info;
	start(&info, host, port);

    try {
        connectTo(info);
    } catch (NetworkError& e) {
        freeaddrinfo(info);
        throw;
    }
}

void NetworkConnection::start(struct addrinfo** addr_results, 
                          const char* host, const char* port) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    int gai_output;
    if ((gai_output = getaddrinfo(host, port, &hints, addr_results)) != 0) {
        throw NetworkError("Error executing getaddrinfo: %s\n",
                                  gai_strerror(gai_output));
    }
}

void NetworkConnection::connectTo(struct addrinfo* addr_results) {
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
        // Connect
        if (connect(new_socket, addr_copy->ai_addr, 
                    addr_copy->ai_addrlen) == -1) {
            error_msg = "Error connecting: ";
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

void NetworkConnection::sendMsg(const std::string& message) {
    sendMsg(message.c_str(), message.size());
}

void NetworkConnection::sendMsg(const char* message, size_t message_length) {
    size_t total_bytes_sent = 0;
    while (total_bytes_sent < message_length) {
        ssize_t bytes_sent = send(this->file_descriptor, 
                                 &message[total_bytes_sent], 
                                 message_length - total_bytes_sent,
                                 MSG_NOSIGNAL);
        if (bytes_sent == 0) { return; }
        if (bytes_sent == -1) {
            throw NetworkError("Error sending: %s\n", strerror(errno));
        }
        total_bytes_sent += bytes_sent;
    }
}

std::string NetworkConnection::recvMsg() {
    ssize_t bytes_recv = -1;
    std::string message;
    char buffer[BUFFER_LENGTH];
    memset(&buffer, 0, BUFFER_LENGTH);

    while ((bytes_recv = recvMsg(buffer, BUFFER_LENGTH)) != 0) {
        message.append(buffer, bytes_recv);
        memset(&buffer, 0, BUFFER_LENGTH);
    }
    return message;
}

size_t NetworkConnection::recvMsg(char* message, size_t buff_length) {
    size_t total_bytes_recv = 0;
    while (total_bytes_recv < buff_length) {
        ssize_t bytes_recv = recv(this->file_descriptor, 
                                 &message[total_bytes_recv], 
                                 buff_length - total_bytes_recv, 0);
        if (bytes_recv == 0) return total_bytes_recv;
        if (bytes_recv == -1) {
            throw NetworkError("Error receiving: %s\n",
                                      strerror(errno));
        }
        total_bytes_recv += bytes_recv;
    }
    return total_bytes_recv;
}

bool NetworkConnection::isValid() const {
    return this->file_descriptor != -1;
}

void NetworkConnection::stopSending() {
    shutdown(this->file_descriptor, SHUT_WR);
}

void NetworkConnection::closeSocket() {
    shutdown(this->file_descriptor, SHUT_RDWR);
    if (isValid()) close(this->file_descriptor);
}

NetworkConnection::NetworkConnection(NetworkConnection&& other) {
    this->file_descriptor = other.file_descriptor;
    other.file_descriptor = -1;
}
NetworkConnection& NetworkConnection::operator=(NetworkConnection&& other) {
    this->file_descriptor = other.file_descriptor;
    other.file_descriptor = -1;
    return *this;
}

NetworkConnection::~NetworkConnection() {
    /*
    if (isValid()) {
        shutdown(this->file_descriptor, SHUT_RDWR);
        close(this->file_descriptor);
        this->file_descriptor = -1;
    }
     */
}