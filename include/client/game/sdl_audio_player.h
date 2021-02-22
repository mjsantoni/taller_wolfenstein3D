//
// Created by andy on 27/11/20.
//

#ifndef TP_WOLFENSTEIN_SDLAUDIOPLAYER_H
#define TP_WOLFENSTEIN_SDLAUDIOPLAYER_H

#include <string>
#include <mutex>
#include "client/sdl_exception.h"

class SdlAudioPlayer {
private:
  std::mutex m;
 public:
  SdlAudioPlayer();
  void playSound(const std::string& file_name);
  void playSound(const std::string& file_name, double volume_ratio);
  static void restoreVolume();
  void setVolume(int volume_level);
  void playMusic(const std::string& file_name);
  void playMusic(const std::string& file_name, int volume);
  void stopMusic();
  static void setMusicVolume(int volume);
  static void restoreMusicVolume();
};

#endif //TP_WOLFENSTEIN_SDLAUDIOPLAYER_H
