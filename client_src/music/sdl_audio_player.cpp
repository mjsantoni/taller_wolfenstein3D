//
// Created by andy on 27/11/20.
//

#include <SDL_mixer.h>
#include "client/sdl_audio_player.h"
#include "client/sdl_exception.h"

SdlAudioPlayer::SdlAudioPlayer() {
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        throw SdlException( "Error en la inicializacion del audio",
                            Mix_GetError());
}

void SdlAudioPlayer::playSong(const std::string& file_name) {
    Mix_Music* gMusic = Mix_LoadMUS(file_name.c_str());
    if(!gMusic) {
        throw SdlException( "Error en la carga del audio", Mix_GetError());
    }
    Mix_PlayMusic(gMusic, -1);
}

void SdlAudioPlayer::stopSong() {
    Mix_HaltMusic();
}
