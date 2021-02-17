//
// Created by andy on 17/2/21.
//

#include <string>
#include <cstring>
#include "common/connection_exception.h"

ConnectionException::ConnectionException(const char* message) noexcept {
    size_t msg_length =  std::string(message).length();
    strncpy(msg_error, message, msg_length);
    msg_error[msg_length] = '\0';
}

ConnectionException::~ConnectionException() noexcept = default;

const char *ConnectionException::what() const noexcept {
    return msg_error;
}
