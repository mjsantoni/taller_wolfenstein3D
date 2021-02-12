//
// Created by andy on 7/2/21.
//

#ifndef TP_WOLFENSTEIN_AUDIO_MANAGER_H
#define TP_WOLFENSTEIN_AUDIO_MANAGER_H

#include <zconf.h>
#include <client/game/sdl_audio_player.h>
#include <mutex>

class AudioManager {
private:
    SdlAudioPlayer audio_player;
public:
    void playSong();
    void stopSong();
    void stopSound();
    void displayPlayerAttackingSound(int equipped_weapon);
    void displayKnifeStabbingSound();
    void displayPlayerShootingSound();
    void displayEmptyGunSound();
    std::mutex m;
};


#endif //TP_WOLFENSTEIN_AUDIO_MANAGER_H