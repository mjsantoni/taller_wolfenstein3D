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
    std::mutex m;
    SdlAudioPlayer audio_player;
    std::string files_path = "../client_src/resources/sounds/";
public:
    void playSong();
    void stopSong();
    void stopSound();
    void displayPlayerAttackingSound(int equipped_weapon);
    void displayKnifeStabbingSound();
    void displayPlayerShootingSound();
    void displayEmptyGunSound();
    void displayExplosionSound(double volume_ratio);

    void displayPlayerLosingHealthSound();
    std::string getFilePath(const std::string &file_name);
    void displayEnemyShot(double volume_ratio);
    void displayDyingEnemy(double volume_ratio);
    void displayDogAttackingSound(double volume_ratio);
    void displayDogGettingHit(double volume_ratio);
    void displayHumanGettingHit(double volume_ratio);
    void displayDyingDog(double volume_ratio);
    void playAmmoPickUpSound();
    void playItemPickUpSound();
    void playDoorOpeningSound();
    void displayFakeWallDisappearingSound();
    void playVictorySong();
    void playDefeatSong();
};


#endif //TP_WOLFENSTEIN_AUDIO_MANAGER_H
