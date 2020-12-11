//
// Created by andy on 11/12/20.
//

#ifndef TP_WOLFENSTEIN_FILEEXCEPTION_H
#define TP_WOLFENSTEIN_FILEEXCEPTION_H

#include <exception>
#define BUF_LEN 256

class FileException : std::exception {
private:
    char msg_error[BUF_LEN];
public:
    explicit FileException(const char* message) noexcept;
    const char* what() const noexcept override;
    virtual ~FileException() noexcept;

};


#endif //TP_WOLFENSTEIN_FILEEXCEPTION_H
