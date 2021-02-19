#include <algorithm>
#include "server/game/score_handler.h"

void ScoreHandler::addKill(int id, int n) {
    auto iterator = kills.find(id);
    if (iterator == kills.end())
        kills[id] = n;
    else
        kills[id] += n;
}

void ScoreHandler::addBulletsShot(int id, int n) {
    auto iterator = bulletsShot.find(id);
    if (iterator == bulletsShot.end())
        bulletsShot[id] = n;
    else
        bulletsShot[id] += n;
}

void ScoreHandler::addTreasurePoints(int id, int n) {
    auto iterator = treasurePoints.find(id);
    if (iterator == treasurePoints.end())
        treasurePoints[id] = n;
    else
        treasurePoints[id] += n;
}

std::vector<std::pair<int,int>> ScoreHandler::getTopFraggers(int n) { return getTop(kills, n); }
std::vector<std::pair<int,int>> ScoreHandler::getTopShooters(int n) { return getTop(bulletsShot, n); }
std::vector<std::pair<int,int>> ScoreHandler::getTopCollectors(int n) { return getTop(treasurePoints, n); }

/* SORT MAP */

bool cmp(std::pair<int,int> n1, std::pair<int,int> n2) { return n1.second > n2.second; };

std::vector<std::pair<int,int>> sortMap(const std::unordered_map<int,int>& map) {
    std::vector<std::pair<int,int>> sorted;
    for (auto& elem : map) sorted.emplace_back(elem);
    std::sort(sorted.begin(), sorted.end(), cmp);
    return sorted;
}

std::vector<std::pair<int,int>> ScoreHandler::getTop(const std::unordered_map<int,int>& map, int n) {
    std::vector<std::pair<int,int>> topN = sortMap(map);
    if (n > topN.size()) n = topN.size();
    if (n < 0) n = 0;
    topN = std::vector<std::pair<int,int>>(topN.begin(), topN.begin() + n);
    return topN;
}
