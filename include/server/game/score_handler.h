#ifndef TP_WOLFENSTEIN_SCORE_HANDLER_H
#define TP_WOLFENSTEIN_SCORE_HANDLER_H

#include <map>
#include <vector>
#include <unordered_map>

class ScoreHandler {
private:
    std::unordered_map<int,int> kills;
    std::unordered_map<int,int> bulletsShot;
    std::unordered_map<int,int> treasurePoints;

    std::vector<std::pair<int,int>> getTop(const std::unordered_map<int,int>& map, int n);

public:

    ScoreHandler() = default;

    void addKill(int id, int n);
    void addBulletsShot(int id, int n);
    void addTreasurePoints(int id, int n);

    std::vector<std::pair<int,int>> getTopFraggers(int n);
    std::vector<std::pair<int,int>> getTopShooters(int n);
    std::vector<std::pair<int,int>> getTopCollectors(int n);
};


#endif //TP_WOLFENSTEIN_SCORE_HANDLER_H
