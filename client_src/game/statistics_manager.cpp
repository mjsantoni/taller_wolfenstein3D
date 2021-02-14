//
// Created by andy on 13/2/21.
//

#include "client/game/statistics_manager.h"

void StatisticsManager::addStatistic(int statistic_type, int value) {
    switch (statistic_type) {
        case TOP_KILLER:
            statistics_vector[0] = value;
            break;
        case TOP_SHOOTER:
            statistics_vector[1] = value;
            break;
        default:
            statistics_vector[2] = value;
            break;
    }
}

bool StatisticsManager::readyToShow() {
    return statistics_vector.size() == 3;
}

std::vector<int> StatisticsManager::getStatistics() {
    return statistics_vector;
}
