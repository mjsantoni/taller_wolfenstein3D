//
// Created by andy on 27/11/20.
//

#include <SDL_mixer.h>
#include <iostream>
#include "client/game/sdl_audio_player.h"

void setVolume(int volume_level);

SdlAudioPlayer::SdlAudioPlayer() {
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    throw SdlException("Error en la inicializacion del audio",
                       Mix_GetError());
}

void SdlAudioPlayer::playSound(const std::string& file_name) {
  std::unique_lock<std::mutex> lock(m);
  Mix_Chunk* sound = Mix_LoadWAV(file_name.c_str());
  if (!sound) {
    throw SdlException("Error en la carga del audio", Mix_GetError());
  }
  Mix_PlayChannel(-1, sound, 0);
  restoreVolume();
}

void SdlAudioPlayer::playSound(const std::string& file_name,
                               double volume_ratio) {
  int volume = (int) (volume_ratio * MIX_MAX_VOLUME);
  Mix_Volume(-1, volume);
  std::unique_lock<std::mutex> lock(m);
  Mix_Chunk* sound = Mix_LoadWAV(file_name.c_str());
  if (!sound) {
    throw SdlException("Error en la carga del audio", Mix_GetError());
  }
  Mix_PlayChannel(-1, sound, 0);
  restoreVolume();
}

void SdlAudioPlayer::playMusic(const std::string& file_name) {
  std::unique_lock<std::mutex> lock(m);
  Mix_Music* gMusic = Mix_LoadMUS(file_name.c_str());
  if (!gMusic) {
    throw SdlException("Error en la carga del audio", Mix_GetError());
  }
  Mix_PlayMusic(gMusic, -1);
  restoreVolume();
}

void SdlAudioPlayer::setVolume(int volume_level) {
  std::unique_lock<std::mutex> lock(m);
  Mix_Volume(1, volume_level);
}

void SdlAudioPlayer::restoreVolume() {
  Mix_Volume(1, MIX_MAX_VOLUME);
}

void SdlAudioPlayer::playMusic(const std::string& file_name, int volume) {
  std::unique_lock<std::mutex> lock(m);
  Mix_Music* gMusic = Mix_LoadMUS(file_name.c_str());
  if (!gMusic) {
    throw SdlException("Error en la carga del audio", Mix_GetError());
  }
  Mix_VolumeMusic(volume);
  Mix_PlayMusic(gMusic, -1);
}

void SdlAudioPlayer::stopMusic() {
  std::unique_lock<std::mutex> lock(m);
  Mix_HaltMusic();
}

void SdlAudioPlayer::setMusicVolume(int volume) {
  Mix_VolumeMusic(volume);
}

void SdlAudioPlayer::restoreMusicVolume() {
  Mix_VolumeMusic(MIX_MAX_VOLUME);
}

