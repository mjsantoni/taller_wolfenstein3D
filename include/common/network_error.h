#ifndef NETWORK_ERROR_H
#define NETWORK_ERROR_H
#include <typeinfo>

#define BUF_LENGTH 256

class NetworkError : public std::exception {
    private:
        char msg_error[BUF_LENGTH];

    public:
        explicit NetworkError(const char* format, ...) noexcept;
        virtual const char* what() const noexcept;
        virtual ~NetworkError() noexcept {}
};

#endif // NETWORK_ERROR_H
