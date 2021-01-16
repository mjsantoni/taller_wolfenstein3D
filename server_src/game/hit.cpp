#include "server/game/hit.h"

Hit::Hit(int _player_id, int _bullets_shot,
         std::vector<std::pair<int, int>> _enemy_dmg_done) :
                    player_id(_player_id),
                    bullets_shot(_bullets_shot),
                    enemy_dmg_done(_enemy_dmg_done) {}

Hit::~Hit() {}

int Hit::getPlayerId() const {
    return player_id;
}

int Hit::getBulletsShot() const {
    return bullets_shot;
}

//Esta funcion podria ser mejorada para no recorrer muchas veces el vector de daño
//en caso de que hitee mucha gente (poco probable)
std::vector<std::pair<int, int>> Hit::getEnemyDmgDone(int max_players) {
    std::vector<std::pair<int, int>> total_dmg;
    int total = 0;
    for (int i = 0; i < max_players; i++) {
        for (auto& dmg : enemy_dmg_done) {
            if (dmg.first == i) total += dmg.second;
        }
        total_dmg.emplace_back(i, total);
        total = 0;
    }
    return total_dmg;
}
