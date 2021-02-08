//
// Created by andy on 7/2/21.
//


#include "client/sounds/audio_manager.h"

void AudioManager::playSong() {
    audio_player.playSound("../client_src/resources/sounds/music.wav");
}

void AudioManager::stopSong() {
    audio_player.stopSound();
}

void AudioManager::stopSound() {
    audio_player.stopSound();
}

void AudioManager::displayPlayerShootingSound() {
    audio_player.playSound("../client_src/resources/sounds/gun_fire.wav");
    usleep(200000);
    audio_player.stopSound();
}

void AudioManager::displayEmptyGunSound() {
    audio_player.playSound("../client_src/resources/sounds/empty_gun.mp3");
    usleep(200000);
    audio_player.stopSound();
}

void AudioManager::displayPlayerAttackingSound(int equipped_weapon) {
    switch (equipped_weapon) {
        case 1:
            displayKnifeStabbingSound();
            break;
        default:
            displayPlayerShootingSound();
            break;
    }
}

void AudioManager::displayKnifeStabbingSound() {
    audio_player.playSound("../client_src/resources/sounds/knife_stab.mp3");
    usleep(200000);
    audio_player.stopSound();
}
