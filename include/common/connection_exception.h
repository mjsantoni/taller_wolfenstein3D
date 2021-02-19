#ifndef TP_WOLFENSTEIN_CONNECTION_EXCEPTION_H
#define TP_WOLFENSTEIN_CONNECTION_EXCEPTION_H

#include <exception>
#define BUF_LEN 256

class ConnectionException : public std::exception {
private:
    char msg_error[BUF_LEN];
public:
    explicit ConnectionException(const char* message) noexcept;
    const char* what() const noexcept override;
    virtual ~ConnectionException() noexcept;
};

#endif //TP_WOLFENSTEIN_CONNECTION_EXCEPTION_H
