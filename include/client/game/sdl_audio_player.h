//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_SDLAUDIOPLAYER_H
#define TP_WOLFENSTEIN_SDLAUDIOPLAYER_H

#include <string>
#include <mutex>
#include "client/sdl_exception.h"

class SdlAudioPlayer {
 public:
  SdlAudioPlayer();
  void playSound(const std::string& file_name);
  void playSound(const std::string& file_name, double volume_ratio);
  void stopSound();
  std::mutex m;
  void restoreVolume();
  void setVolume(int volume_level);
  void playMusic(const std::string& file_name);
  void playMusic(const std::string& file_name, int volume);
  void stopMusic();
  void setMusicVolume(int volume);
  void restoreMusicVolume();
};

#endif //TP_WOLFENSTEIN_SDLAUDIOPLAYER_H
