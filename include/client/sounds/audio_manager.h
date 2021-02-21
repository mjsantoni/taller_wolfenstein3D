//
// Created by andy on 7/2/21.
//

#ifndef TP_WOLFENSTEIN_AUDIO_MANAGER_H
#define TP_WOLFENSTEIN_AUDIO_MANAGER_H

#include <zconf.h>
#include <client/game/sdl_audio_player.h>
#include <mutex>
#include "../../../client_src/client_routes.h"

class AudioManager {
private:
    std::mutex m;
    SdlAudioPlayer audio_player;
    std::string files_path = CLIENT_SOUNDS_ROUTE;
public:
    void playSong();
    void stopSong();
    void stopSound();
    void displayPlayerAttackingSound(int equipped_weapon);
    void displayKnifeStabbingSound();
    void displayPlayerPistolSound(double volume_ratio);
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
    void displayRocketLauncherSound(double volume_ratio);
    void displayMachineGunSound(double volume_ratio);
};


#endif //TP_WOLFENSTEIN_AUDIO_MANAGER_H
