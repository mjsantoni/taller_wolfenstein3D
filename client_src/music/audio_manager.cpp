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
    audio_player.playSound(getFilePath("empty_gun.mp3"), 200000);
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
    audio_player.playSound(getFilePath("knife_stab.mp3"), 200000);
}

void AudioManager::displayPlayerShootingSound() {
    audio_player.playSound(getFilePath("gun_fire.wav"), 200000);
}

void AudioManager::displayExplosionSound() {
    std::unique_lock<std::mutex> lock(m);
    audio_player.playSound(getFilePath("explosion.mp3"), 500000);
}

void AudioManager::displayDyingEnemy(double volume_ratio) {
    audio_player.setVolume((int) (volume_ratio * MAX_VOLUME));
    std::unique_lock<std::mutex> lock(m);
    audio_player.playSound(getFilePath("dead_enemy.mp3"), 400000);
}

void AudioManager::displayEnemyShot(double volume_ratio) {
    std::unique_lock<std::mutex> lock(m);
    audio_player.playSound(getFilePath("enemy_shot.mp3"), 200000);
}

void AudioManager::displayPlayerLosingHealthSound() {
    std::unique_lock<std::mutex> lock(m);
    audio_player.playSound(getFilePath("losing_health.mp3"), 500000);
}

void AudioManager::displayDogAttackingSound(double volume_ratio) {
    audio_player.setVolume((int) (volume_ratio * MAX_VOLUME));
    audio_player.playSound(getFilePath("dog_growling.mp3"), 500000);
}

void AudioManager::displayDogGettingHit(double volume_ratio) {
    audio_player.setVolume((int) (volume_ratio * MAX_VOLUME));
    audio_player.playSound(getFilePath("dog_hurt.mp3"), 500000);
}

void AudioManager::displayHumanGettingHit(double volume_ratio) {
    audio_player.setVolume((int) (volume_ratio * MAX_VOLUME));
    audio_player.playSound(getFilePath("enemy_hurt.mp3"), 500000);
}

void AudioManager::displayDyingDog(double volume_ratio) {
    audio_player.setVolume((int) (volume_ratio * MAX_VOLUME));
    audio_player.playSound(getFilePath("dog_death.mp3"));
    //usleep(500000);
    //audio_player.stopSound();
    //audio_player.restoreVolume();
}

void AudioManager::displayPickUpSound() {
    audio_player.playSound(getFilePath("item_pick_up.mp3"), 400000);
}

std::string AudioManager::getFilePath(std::string file_name) {
    return files_path + "/" + file_name;
}
