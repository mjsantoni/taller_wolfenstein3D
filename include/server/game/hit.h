#ifndef TP_WOLFENSTEIN_HIT_H
#define TP_WOLFENSTEIN_HIT_H
#include <vector>

class Hit {
private:
    int player_id;
    int bullets_shot;
    std::vector<std::pair<int, int>> enemy_dmg_done;
    bool used_all_ammo;

public:
    Hit(int _player_id, int _bullets_shot,
        std::vector<std::pair<int, int>> _enemy_dmg_done, bool _used_all_ammo);

    int getPlayerId() const;

    int getBulletsShot() const;

    bool usedAllAmmo() const;

    std::vector<std::pair<int, int>> getEnemyDmgDone(int max_players);
    // (enemy_id, dmg)



    ~Hit();
    Hit(const Hit& other);
    Hit& operator=(const Hit& other);


    bool playerDied();
};


#endif //TP_WOLFENSTEIN_HIT_H
