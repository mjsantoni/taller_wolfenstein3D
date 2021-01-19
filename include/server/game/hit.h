#ifndef TP_WOLFENSTEIN_HIT_H
#define TP_WOLFENSTEIN_HIT_H
#include <vector>
#include "server/game/coordinate.h"

class Hit {
private:
    int player_id;
    int bullets_shot;
    std::vector<std::pair<int, int>> enemy_dmg_done;
    bool used_all_ammo;
    std::vector<std::pair<int, bool>> player_respawns;
    std::vector<std::pair<int, Coordinate>> drops;

public:
    Hit(int _player_id, int _bullets_shot,
        std::vector<std::pair<int, int>> _enemy_dmg_done, bool _used_all_ammo);

    int getPlayerId() const;

    int getBulletsShot() const;

    bool usedAllAmmo() const;

    std::vector<std::pair<int, int>> getEnemyDmgDone(int max_players);
    // (enemy_id, dmg)

    std::vector<int> getDeadPlayers();
    const std::vector<std::pair<int, bool>> &getPlayerRespawns() const;
    const std::vector<std::pair<int, Coordinate>> &getDrops() const;

    bool playerDied();

    void setPlayerRespawns(std::vector<std::pair<int, bool>> vector);

    void addDrops(int id, Coordinate pos);
    ~Hit();
    Hit(const Hit& other);
    Hit& operator=(const Hit& other);
};


#endif //TP_WOLFENSTEIN_HIT_H
