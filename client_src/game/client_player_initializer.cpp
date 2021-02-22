#include "client/game/client_player_initializer.h"
#include "client_routes.h"

ClientPlayerInitializer::ClientPlayerInitializer() :
    config_parser(CONFIG_PATH) {

}

void ClientPlayerInitializer::initializePlayer(ClientPlayer& player) {
  int max_bullets = config_parser.getSpecificCategory("player", "max_bullets");
  int max_hp = config_parser.getSpecificCategory("player", "max_hp");
  int bullets = config_parser.getSpecificCategory("player", "bullets");
  int max_lives = config_parser.getSpecificCategory("player", "max_lives");
  player.setMaxAmmo(max_bullets);
  player.setMaxHealth(max_hp);
  player.setAmmo(bullets);
  player.setFullAmmo(bullets);
  player.setMaxLives(max_lives);
  player.setLives(max_lives);
  player.setHealth(max_hp);
}