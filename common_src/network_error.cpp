#include "common/network_error.h"
#include <cstdarg>
#include <cstdio>

NetworkError::NetworkError(const char* format, ...) noexcept {
  va_list args;
  va_start(args, format);
  vsnprintf(this->msg_error, BUF_LENGTH, format, args);
  va_end(args);
}

const char* NetworkError::what() const noexcept {
  return this->msg_error;
}
