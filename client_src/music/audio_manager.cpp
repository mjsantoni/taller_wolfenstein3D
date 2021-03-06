//
// Created by andy on 7/2/21.
//

#include "client/sounds/audio_manager.h"

#define MAX_VOLUME 128

void AudioManager::displayEmptyGunSound() {
  audio_player.playSound(getFilePath("empty_gun.mp3"), 200000);
}

void AudioManager::displayKnifeStabbingSound() {
  audio_player.playSound(getFilePath("knife_stab.mp3"));
}

void AudioManager::displayPlayerPistolSound(double volume_ratio) {
  audio_player.playSound(getFilePath("gun_fire.wav"), volume_ratio);
}

void AudioManager::displayExplosionSound(double volume_ratio) {
  audio_player.playSound(getFilePath("explosion.mp3"), volume_ratio);
}

void AudioManager::displayDyingEnemy(double volume_ratio) {
  audio_player.playSound(getFilePath("dead_enemy.mp3"), volume_ratio);
}

void AudioManager::displayPlayerLosingHealthSound() {
  audio_player.playSound(getFilePath("losing_health.mp3"));
}

void AudioManager::displayDogAttackingSound(double volume_ratio) {
  audio_player.playSound(getFilePath("dog_growling.mp3"), volume_ratio);
}

void AudioManager::displayDogGettingHit(double volume_ratio) {
  audio_player.playSound(getFilePath("dog_hurt.mp3"), volume_ratio);
}

void AudioManager::displayHumanGettingHit(double volume_ratio) {
  audio_player.playSound(getFilePath("enemy_hurt.mp3"), volume_ratio);
}

void AudioManager::displayDyingDog(double volume_ratio) {
  audio_player.playSound(getFilePath("dog_death.mp3"), volume_ratio);
}

void AudioManager::playAmmoPickUpSound() {
  audio_player.playSound(getFilePath("ammo_pick_up.mp3"));
}

std::string AudioManager::getFilePath(const std::string& file_name) {
  return CLIENT_SOUNDS_ROUTE + file_name;
}

void AudioManager::playVictorySong() {
  audio_player.playMusic(getFilePath("victory_song.mp3"));
}

void AudioManager::playDefeatSong() {
  audio_player.playMusic(getFilePath("defeat_song.mp3"));
}

void AudioManager::playItemPickUpSound() {
  audio_player.playSound(getFilePath("item_pick_up.mp3"));
}

void AudioManager::playDoorOpeningSound() {
  audio_player.playSound(getFilePath("unlocked_door.mp3"));
}

void AudioManager::displayFakeWallDisappearingSound() {
  audio_player.playSound(getFilePath("wall_moving.mp3"));
}

void AudioManager::displayMachineGunSound(double volume_ratio) {
  audio_player.playSound(getFilePath("machine_gun.mp3"), volume_ratio);
}

void AudioManager::displayRocketLauncherSound(double volume_ratio) {
  audio_player.playSound(getFilePath("rocket_launcher.mp3"), volume_ratio);
}

void AudioManager::playGameSong() {
  audio_player.playMusic(getFilePath("whole_song.mp3"));
}

void AudioManager::stopGameSong() {
  audio_player.stopMusic();
  audio_player.restoreMusicVolume();
}

void AudioManager::setMusicVolume(int volume) {
  audio_player.setMusicVolume(volume);
}

void AudioManager::playTimeUpSong() {
  audio_player.playMusic(getFilePath("time_up.wav"));
}
