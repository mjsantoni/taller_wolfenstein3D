//
// Created by andy on 11/12/20.
//

#include <string>
#include <cstring>
#include "client/file_exception.h"

FileException::FileException(const char* message) noexcept {
    size_t msg_length =  std::string(message).length();
    strncpy(msg_error, message, msg_length);
    msg_error[msg_length] = '\0';
}

FileException::~FileException() noexcept = default;

const char *FileException::what() const noexcept {
    return msg_error;
}
