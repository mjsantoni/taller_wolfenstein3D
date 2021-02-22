//
// Created by andy on 13/2/21.
//

#include "client/game/statistics_manager.h"

void StatisticsManager::addStatistic(int statistic_type,
                                     int player_id,
                                     int value) {
  switch (statistic_type) {
    case TOP_KILLER:top_killers_vector.push_back(player_id);
      top_killers_stats.push_back(value);
      break;
    case TOP_SHOOTER:top_shooters_vector.push_back(player_id);
      top_shooters_stats.push_back(value);
      break;
    case TOP_SCORER:top_scorers_vector.push_back(player_id);
      top_scorers_stats.push_back(value);
      break;
    default:break;
  }
}

std::vector<std::vector<int>> StatisticsManager::getStatistics() {
  std::vector<std::vector<int>> combined_vector;
  combined_vector.push_back(top_killers_vector);
  combined_vector.push_back(top_shooters_vector);
  combined_vector.push_back(top_scorers_vector);
  combined_vector.push_back(top_killers_stats);
  combined_vector.push_back(top_shooters_stats);
  combined_vector.push_back(top_scorers_stats);
  return combined_vector;
}
