//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_SDLAUDIOPLAYER_H
#define TP_WOLFENSTEIN_SDLAUDIOPLAYER_H

#include <string>
#include "client/sdl_exception.h"

class SdlAudioPlayer {
public:
    SdlAudioPlayer();
    void playSound(const std::string& file_name);
    void stopSound();
};


#endif //TP_WOLFENSTEIN_SDLAUDIOPLAYER_H
