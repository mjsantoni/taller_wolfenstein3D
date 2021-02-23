//
// Created by andy on 25/11/20.
//

#include <fstream>
#include <sstream>
#include <iterator>
#include <zconf.h>
#include <functional>
#include <iostream>
#include <client/graphics/ray_info.h>
#include "client/game/client_map.h"

ClientMap::ClientMap(int width, int height, int grid_size) :
    board(GRID_SIZE, drawables_by_position),
    width(width),
    height(height) {
  real_width = width * grid_size;
  real_height = height * grid_size;
  max_distance = Calculator::calculateDistance(real_width, real_height);
}

ClientMap::ClientMap() : width(0),
                         height(0),
                         real_width(0),
                         real_height(0),
                         grid_size(GRID_SIZE),
                         board(GRID_SIZE, drawables_by_position) {
}

int ClientMap::getGridSize() {
  return grid_size;
}

bool ClientMap::outOfHorizontalBounds(int x_pos) {
  return x_pos < 0 || x_pos > real_width;
}

bool ClientMap::outOfVerticalBounds(int y_pos) {
  return y_pos < 0 || y_pos > real_height;
}

int ClientMap::getMaxDistance() {
  return (int) (Calculator::calculateDistance(real_width, real_height));
}

bool ClientMap::wallAtGrid(int x_pos, int y_pos, int x_factor, int y_factor) {
  return board.wallAtGrid(x_pos, y_pos, x_factor, y_factor);
}

void ClientMap::getMapInfoForWall(RayInfo& ray_info,
                                  int x_pos,
                                  int y_pos,
                                  int x_factor,
                                  int y_factor) {
  board.getMapInfoForWall(ray_info, x_pos, y_pos, x_factor, y_factor);
}

void ClientMap::putWallAt(std::pair<int, int> coordinates, int object_type) {
  board.putWallAt(coordinates, object_type);
}

void ClientMap::putObjectAt(int object_type, int x_pos, int y_pos) {
  board.putObjectAt(object_type, x_pos, y_pos);
}

void ClientMap::moveEnemy(int enemy_id, int x_pos, int y_pos) {
  if (enemies.find(enemy_id) == enemies.end())
    return;
  Drawable& enemy = enemies.at(enemy_id);
  enemy.setMapPosition(x_pos, y_pos);
  ImageManager::setMovingAnimationForEnemy(enemy,
                                           enemy.getSpriteAnimationNo());
}

int ClientMap::getWidth() {
  return real_width;
}

int ClientMap::getHeight() {
  return real_height;
}

std::vector<Drawable> ClientMap::getAllDrawables() {
  std::vector<Drawable> objects_vector;
  for (auto& pair : objects) {
    objects_vector.push_back(pair.second);
  }
  for (auto& pair : enemies) {
    objects_vector.push_back(pair.second);
  }
  for (auto& pair : effects) {
    objects_vector.push_back(pair.second);
  }
  return objects_vector;
}

void ClientMap::removeObject(int object_id) {
  std::pair<int, int> object_position;
  if (objects.find(object_id) != objects.end())
    object_position = objects.at(object_id).getMapPosition();
  if (walls.find(object_id) != walls.end())
    object_position = walls.at(object_id).getMapPosition();
  objects.erase(object_id);
  walls.erase(object_id);
  drawables_by_position.erase(object_position);
}

void ClientMap::updateUnlockedDoor(int object_id, int x_pos, int y_pos) {
  Drawable door(UNLOCKED_DOOR);
  board.updateUnlockedDoor(door, object_id, x_pos, y_pos);
  walls.insert(std::pair<int, Drawable>(object_id, door));
}

void ClientMap::processRPGMissile(int object_id,
                                  int new_x,
                                  int new_y) {
  if (objects.find(object_id) == objects.end())
    return createRPGMissile(object_id, new_x, new_y);
  updateRPGMissile(object_id, new_x, new_y);
}

void ClientMap::createRPGMissile(int object_id,
                                 int new_x,
                                 int new_y) {
  Drawable missile(EFFECT_MISSILE);
  int delta_x = new_x - player_coord.first;
  int delta_y = new_y - player_coord.second;
  double distance = Calculator::calculateDistance(delta_x, delta_y);
  if (distance > grid_size)
    missile = Drawable(EFFECT_INCOMING_MISSILE);
  missile.setMapPosition(new_x, new_y);
  missile.setId(object_id);
  objects.insert(std::pair<int, Drawable>(object_id, missile));
}

void ClientMap::updateRPGMissile(int object_id, int new_x, int new_y) {
  Drawable& missile = objects.at(object_id);
  missile.setMapPosition(new_x, new_y);
}

double ClientMap::setRPGMissileExplosion(int object_id, int exp_x, int exp_y) {
  removeObject(object_id);
  Drawable explosion(EFFECT_EXPLOSION, 3);
  explosion.setMapPosition(exp_x, exp_y);
  int delta_x = player_coord.first - exp_x;
  int delta_y = player_coord.first - exp_y;
  double explosion_distance = Calculator::calculateDistance(delta_x, delta_y);
  double distance_ratio = explosion_distance / max_distance;
  effects.insert(std::pair<int, Drawable>(EXPLOSION_EFFECT_ID, explosion));
  return distance_ratio;
}

void ClientMap::setDimensions(int _width, int _height) {
  width = _width;
  height = _height;
  real_width = width * grid_size;
  real_height = height * grid_size;
  max_distance = Calculator::calculateDistance(real_width, real_height);
  board.setDimensions(_width, _height);
}

void
ClientMap::putObjectAt(int object_id, int object_type, int x_pos, int y_pos) {
  Drawable drawable(object_type);
  drawable.setId(object_id);
  drawable.setMapPosition(x_pos, y_pos);
  objects.insert(std::pair<int, Drawable>{object_id, drawable});
  std::pair<int, int> coords{x_pos, y_pos};
  drawables_by_position.insert(std::pair<std::pair<int, int>, Drawable>
                                   {coords, drawable});
}

void ClientMap::addPlayerSpawnAt(int x_pos, int y_pos) {
  player_spawns.emplace_back(x_pos, y_pos);
}

void ClientMap::addPlayers(int number_of_players, int own_player_id) {
  for (int i = 0; i < number_of_players; ++i) {
    if (i == own_player_id)
      continue;
    std::pair<int, int> player_pos = player_spawns[i];
    putEnemyAt(player_pos.first, player_pos.second, ENEMY_GUARD, i);
  }
}

void ClientMap::putEnemyAt(int x_pos, int y_pos, int object_type, int id) {
  Drawable enemy(object_type);
  enemy.setId(id);
  enemy.setMapPosition(x_pos, y_pos);
  enemies.insert(std::pair<int, Drawable>(id, enemy));
}

std::pair<int, int> ClientMap::getSpawnPositionForPlayer(int player_id) {
  return player_spawns[player_id];
}

void ClientMap::updateTotalPlayers(int _total_players) {
  total_players = _total_players;
}

void ClientMap::respawnPlayer(int player_id) {
  Drawable& enemy = enemies.at(player_id);
  ImageManager::setDyingAnimationForEnemy(enemy);
  enemies_to_respawn.insert(player_id);
}

void ClientMap::changeEnemyImage(int player_id, int weapon) {
  Drawable& current_drawable = enemies.at(player_id);
  int object_type = ImageManager::getImageNumberFromWeapon(weapon);
  Drawable new_drawable(object_type);
  new_drawable.setMapPosition(current_drawable.getMapPosition());
  new_drawable.setId(player_id);
  enemies.erase(player_id);
  enemies.insert(std::pair<int, Drawable>(player_id, new_drawable));
}

void ClientMap::updateEnemiesSprites() {
  for (auto& pair : enemies) {
    Drawable& enemy = pair.second;
    int current_animation = enemy.getSpriteAnimationNo();
    ImageManager::setMovingAnimationForEnemy(enemy, current_animation);
  }
}

void ClientMap::addEnemies(int own_player_id) {
  for (int i = 0; i < total_players; ++i) {
    if (i == own_player_id)
      continue;
    std::pair<int, int> player_coords = player_spawns[i];
    int player_x = player_coords.first;
    int player_y = player_coords.second;
    putEnemyAt(player_x, player_y, ENEMY_GUARD, i);
  }
}

void ClientMap::addObjectId(int object_id, int x_pos, int y_pos) {
  std::pair<int, int> object_coords{x_pos, y_pos};
  Drawable& drawable = drawables_by_position.at(object_coords);
  drawable.setId(object_id);
  int object_type = drawable.getObjectType();
  Drawable new_drawable(object_type);
  new_drawable.setMapPosition(x_pos, y_pos);
  new_drawable.setId(object_id);
  if (ImageManager::objectIsWall(object_type))
    walls.insert(std::pair<int, Drawable>(object_id, new_drawable));
  else
    objects.insert(std::pair<int, Drawable>(object_id, new_drawable));
}

int ClientMap::getObjectTypeFromId(int object_id) {
  if (objects.find(object_id) != objects.end())
    return objects.at(object_id).getObjectType();
  if (walls.find(object_id) != objects.end())
    return walls.at(object_id).getObjectType();
  return -1;
}

int ClientMap::getEnemyTypeFromId(int enemy_id) {
  if (enemies.find(enemy_id) == objects.end())
    return 0; // deberia lanzarse una excepcion
  Drawable& drawable = enemies.at(enemy_id);
  return drawable.getObjectType();
}

double ClientMap::getEnemyDistanceRatio(int enemy_id) {
  Drawable& enemy = enemies.at(enemy_id);
  std::pair<int, int> enemy_pos = enemy.getMapPosition();
  int delta_x = player_coord.first - enemy_pos.first;
  int delta_y = player_coord.first - enemy_pos.second;
  double enemy_distance = Calculator::calculateDistance(delta_x, delta_y);
  return 1 - (enemy_distance / max_distance);
}

void ClientMap::updateEvents() {
  updateEffects();
  updateDeadEnemies();
  updateRespawnedEnemies();
}

void ClientMap::updateEffects() {
  std::vector<int> effects_to_erase;
  for (auto& pair : effects) {
    if (effects.empty())
      break;
    int id = pair.first;
    Drawable& effect = pair.second;
    effect.reduceDuration();
    if (effect.getDuration() == 0)
      effects_to_erase.push_back(id);
  }
  for (auto& id : effects_to_erase)
    effects.erase(id);
}

void ClientMap::updateDeadEnemies() {
  for (auto& id : enemies_to_swipe) {
    if (enemies_to_swipe.empty())
      break; // NO SE POR QUE TENGO QUE AGREGAR ESTOS BREAKS, PERO NO FUNCIONA BIEN EL FOR
    enemies.erase(id);
    enemies_to_swipe.erase(id);
  }
}

void ClientMap::updateRespawnedEnemies() {
  for (auto& id : enemies_to_respawn) {
    if (enemies_to_respawn.empty())
      break; // NO SE POR QUE TENGO QUE AGREGAR ESTOS BREAKS, PERO NO FUNCIONA BIEN EL FOR
    std::pair<int, int> respawn_position = player_spawns[id];
    Drawable& enemy = enemies.at(id);
    enemy.setObjectType(ENEMY_GUARD);
    enemy.setMapPosition(respawn_position.first, respawn_position.second);
    ImageManager::setMovingAnimationForEnemy(enemy,
                                             enemy.getSpriteAnimationNo());
    enemies_to_respawn.erase(id);
  }
}

void ClientMap::killPlayer(int player_id) {
  Drawable& enemy = enemies.at(player_id);
  ImageManager::setDyingAnimationForEnemy(enemy);
  enemies_to_swipe.insert(player_id);
}

void ClientMap::setEnemyAttacking(int enemy_id) {
  Drawable& enemy = enemies.at(enemy_id);
  ImageManager::setAttackingAnimationForEnemy(enemy);
}

void ClientMap::setBloodEffectForEnemy(int enemy_id) {
  Drawable& enemy = enemies.at(enemy_id);
  std::pair<int, int> enemy_pos = enemy.getMapPosition();
  int enemy_type = enemy.getObjectType();
  Drawable blood_effect(EFFECT_BLOOD, 3);
  int effect_id = effects_handler.getIdForEffect();
  if (enemy_type == ENEMY_DOG)
    blood_effect = Drawable(EFFECT_DOG_BLOOD, 3);
  blood_effect.setMapPosition(enemy_pos);
  effects.insert(std::pair<int, Drawable>(effect_id, blood_effect));
}

bool ClientMap::isLastPlayerStanding() {
  return enemies.size() == 1;
}

int ClientMap::getEnemiesAlive() {
  return enemies.size();
}

void ClientMap::updatePlayerPosition(int x_pos, int y_pos) {
  player_coord.first = x_pos;
  player_coord.second = y_pos;
}
