#include <utility>
#include "server/game/hit.h"
#include <iostream>

Hit::Hit(int _player_id, int _bullets_shot,
         std::vector<std::pair<int, int>> _enemy_dmg_done,
         bool _used_all_ammo) :
                    player_id(_player_id),
                    bullets_shot(_bullets_shot),
                    enemy_dmg_done(std::move(_enemy_dmg_done)),
                    used_all_ammo(_used_all_ammo) {}

Hit::~Hit() {};

int Hit::getPlayerId() const {
    return player_id;
}

int Hit::getBulletsShot() const {
    return bullets_shot;
}

bool Hit::usedAllAmmo() const {
    return used_all_ammo;
}
//Esta funcion podria ser mejorada para no recorrer muchas veces el vector de daño
//en caso de que hitee mucha gente (poco probable)
std::vector<std::pair<int, int>> Hit::getEnemyDmgDone(int max_players) {
    std::vector<std::pair<int, int>> total_dmg; //Vector de (id, dañototal)
    int total = 0;
    //std::cout << "----------------\n";
    for (int i = 0; i < max_players; i++) {
        for (auto& dmg : enemy_dmg_done) {
            if (dmg.first == i) {
                if (dmg.second == -1) continue;
                //std::cout << "Sumo " << dmg.second << " dmg\n";
                total += dmg.second;
            }
        }
        if (total == 0) continue;
        //std::cout << "Daño total hecho a player " << i << ": " << total << "\n";
        total_dmg.emplace_back(i, total);
        total = 0;
    }
    return total_dmg;
}

bool Hit::playerDied() {
    for (auto& dmg : enemy_dmg_done) {
        if (dmg.second == -1) return true;
    }
    return false;
}

std::vector<int> Hit::getDeadPlayers() {
    std::vector<int> dead_players;
    for (auto& dmg : enemy_dmg_done) {
        if (dmg.second == -1) dead_players.push_back(dmg.first);
    }
    return dead_players;
}

void Hit::setPlayersDeaths(std::vector<std::pair<int, bool>> _player_respawns) {
    player_respawns = std::move(_player_respawns);
}

const std::vector<std::pair<int, bool>>& Hit::getPlayerRespawns() const {
    return player_respawns;
}

void Hit::addDrops(std::string type, const Coordinate& pos, int id, int drop_id) {
    drops.emplace_back(type, id, pos, drop_id);
}

const std::vector<Drop>& Hit::getDrops() const {
    return drops;
}

Hit::Hit(const Hit& other) {
    this->player_id = other.player_id;
    this->bullets_shot = other.bullets_shot;
    this->enemy_dmg_done = other.enemy_dmg_done;
    this->used_all_ammo = other.used_all_ammo;
    this->player_respawns = other.player_respawns;
    this->drops = other.drops;
}

Hit& Hit::operator=(const Hit& other) {
    this->player_id = other.player_id;
    this->bullets_shot = other.bullets_shot;
    this->enemy_dmg_done = other.enemy_dmg_done;
    this->used_all_ammo = other.used_all_ammo;
    this->player_respawns = other.player_respawns;
    this->drops = other.drops;
    return *this;
}



