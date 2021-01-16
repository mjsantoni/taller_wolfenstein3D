#ifndef TP_WOLFENSTEIN_HIT_H
#define TP_WOLFENSTEIN_HIT_H
#include <vector>

class Hit {
private:
    int player_id;
    int bullets_shot;
    std::vector<std::pair<int, int>> enemy_dmg_done;

public:
    Hit(int _player_id, int _bullets_shot,
        std::vector<std::pair<int, int>> _enemy_dmg_done);

    int getPlayerId() const;

    int getBulletsShot() const;

    std::vector<std::pair<int, int>> getEnemyDmgDone(int max_players);
    // (enemy_id, dmg)



    ~Hit();


};


#endif //TP_WOLFENSTEIN_HIT_H
