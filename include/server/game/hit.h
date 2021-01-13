#ifndef TP_WOLFENSTEIN_HIT_H
#define TP_WOLFENSTEIN_HIT_H
#include <vector>

class Hit {
private:
    int player_id;
    int bullets_shot;
    std::vector<std::pair<int, int>> enemy_dmg_done; // (enemy_id, dmg)

public:
    Hit(int _player_id, int _bullets_shot,
        std::vector<std::pair<int, int>> _enemy_dmg_done);
    ~Hit();


};


#endif //TP_WOLFENSTEIN_HIT_H
