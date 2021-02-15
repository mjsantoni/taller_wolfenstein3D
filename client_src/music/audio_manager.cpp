//
// Created by andy on 7/2/21.
//

#include "client/sounds/audio_manager.h"

#define MAX_VOLUME 128

void AudioManager::playSong() {
    std::unique_lock<std::mutex> lock(m);
    audio_player.playSound(getFilePath("music.wav"));
}

void AudioManager::stopSong() {
    std::unique_lock<std::mutex> lock(m);
    audio_player.stopSound();
}

void AudioManager::stopSound() {
    std::unique_lock<std::mutex> lock(m);
    audio_player.stopSound();
}

void AudioManager::displayEmptyGunSound() {
    std::unique_lock<std::mutex> lock(m);
    audio_player.playSound(getFilePath("empty_gun.mp3"));
    usleep(200000);
    audio_player.stopSound();
}

void AudioManager::displayPlayerAttackingSound(int equipped_weapon) {
    std::unique_lock<std::mutex> lock(m);
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
    audio_player.playSound(getFilePath("knife_stab.mp3"));
    usleep(200000);
    audio_player.stopSound();
}

void AudioManager::displayPlayerShootingSound() {
    audio_player.playSound("../client_src/resources/sounds/gun_fire.wav");
    usleep(200000);
    audio_player.stopSound();
}

void AudioManager::displayExplosionSound() {
    std::unique_lock<std::mutex> lock(m);
    audio_player.playSound("../client_src/resources/sounds/explosion.mp3");
    usleep(500000);
    audio_player.stopSound();
}

void AudioManager::displayDyingEnemy() {
    std::unique_lock<std::mutex> lock(m);
    audio_player.playSound("../client_src/resources/sounds/dead_enemy.mp3");
    usleep(400000);
    audio_player.stopSound();
}

void AudioManager::displayEnemyShot(double volume_ratio) {
    std::unique_lock<std::mutex> lock(m);
    audio_player.playSound("../client_src/resources/sounds/enemy_shot.mp3");
    usleep(200000);
    audio_player.stopSound();
}

void AudioManager::displayPlayerLosingHealthSound() {
    std::unique_lock<std::mutex> lock(m);
    audio_player.playSound("../client_src/resources/sounds/losing_health.mp3");
    usleep(500000);
    audio_player.stopSound();
}

void AudioManager::displayDogAttackingSound(double volume_ratio) {
    audio_player.setVolume((int) (volume_ratio * MAX_VOLUME));
    audio_player.playSound(getFilePath("dog_growling.mp3"));
    usleep(500000);
    audio_player.stopSound();
    audio_player.restoreVolume();
}

void AudioManager::displayDogGettingHit(double volume_ratio) {
    audio_player.setVolume((int) (volume_ratio * MAX_VOLUME));
    audio_player.playSound(getFilePath("dog_hurt.mp3"));
    usleep(500000);
    audio_player.stopSound();
    audio_player.restoreVolume();
}

void AudioManager::displayHumanGettingHit(double volume_ratio) {
    audio_player.setVolume((int) (volume_ratio * MAX_VOLUME));
    audio_player.playSound(getFilePath("enemy_hurt.mp3"));
    usleep(500000);
    audio_player.stopSound();
    audio_player.restoreVolume();
}


std::string AudioManager::getFilePath(std::string file_name) {
    return files_path + "/" + file_name;
}
