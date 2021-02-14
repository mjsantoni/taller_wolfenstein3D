//
// Created by andy on 13/2/21.
//

#ifndef TP_WOLFENSTEIN_STATISTICS_MANAGER_H
#define TP_WOLFENSTEIN_STATISTICS_MANAGER_H

#include <vector>
#include "common/change.h"

class StatisticsManager {
private:
    std::vector<int> statistics_vector;
public:
    void addStatistic(int statistic_type, int value);
    bool readyToShow();
    std::vector<int> getStatistics();

};


#endif //TP_WOLFENSTEIN_STATISTICS_MANAGER_H
