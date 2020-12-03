//
// Created by andy on 26/11/20.
//

#include <string>
#include <cstring>
#include "SdlException.h"

SdlException::SdlException(const char* message, const char* error) noexcept {
    std::string join(": ");
    std::string string_final = std::string(message) + join + std::string(error);
    strncpy(msg_error, string_final.c_str(),string_final.length());
    msg_error[string_final.length()] = '\0';
}

SdlException::~SdlException() noexcept = default;

const char *SdlException::what() const noexcept {
    return msg_error;
}
