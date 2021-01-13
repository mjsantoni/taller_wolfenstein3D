#include "server/game/hit.h"

Hit::Hit(int _player_id, int _bullets_shot,
         std::vector<std::pair<int, int>> _enemy_dmg_done) :
                    player_id(_player_id),
                    bullets_shot(_bullets_shot),
                    enemy_dmg_done(_enemy_dmg_done) {}

Hit::~Hit() {}