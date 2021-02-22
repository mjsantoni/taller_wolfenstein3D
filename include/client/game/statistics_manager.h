//
// Created by andy on 13/2/21.
//

#ifndef TP_WOLFENSTEIN_STATISTICS_MANAGER_H
#define TP_WOLFENSTEIN_STATISTICS_MANAGER_H

#include <vector>
#include "common/change.h"

class StatisticsManager {
 private:
  std::vector<int> top_killers_vector;
  std::vector<int> top_shooters_vector;
  std::vector<int> top_scorers_vector;
  std::vector<int> top_killers_stats;
  std::vector<int> top_shooters_stats;
  std::vector<int> top_scorers_stats;
  std::vector<int> statistics_vector;
  int max_pos = 0;
 public:
  void addStatistic(int statistic_type, int player_id, int value);
  std::vector<std::vector<int>> getStatistics();

};

#endif //TP_WOLFENSTEIN_STATISTICS_MANAGER_H
