//
// Created by andy on 26/11/20.
//

#ifndef TP_WOLFENSTEIN_SDL_EXCEPTION_H
#define TP_WOLFENSTEIN_SDL_EXCEPTION_H

#include <exception>
#define BUF_LEN 256

class SdlException : std::exception {
public:
    explicit SdlException(const char* message, const char* error) noexcept;
    const char* what() const noexcept override;
    virtual ~SdlException() noexcept;
private:
    char msg_error[BUF_LEN];
};



#endif //TP_WOLFENSTEIN_SDL_EXCEPTION_H
