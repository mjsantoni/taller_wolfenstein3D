//
// Created by andy on 27/11/20.
//

#include <SDL_mixer.h>
#include "client/game/sdl_audio_player.h"

SdlAudioPlayer::SdlAudioPlayer() {
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        throw SdlException( "Error en la inicializacion del audio",
                            Mix_GetError());
}

void SdlAudioPlayer::playSound(const std::string& file_name) {
    std::unique_lock<std::mutex> lock(m);
    Mix_Music* gMusic = Mix_LoadMUS(file_name.c_str());
    if(!gMusic) {
        throw SdlException( "Error en la carga del audio", Mix_GetError());
    }
    Mix_PlayMusic(gMusic, -1);
}

void SdlAudioPlayer::stopSound() {
    std::unique_lock<std::mutex> lock(m);
    Mix_HaltMusic();
}
