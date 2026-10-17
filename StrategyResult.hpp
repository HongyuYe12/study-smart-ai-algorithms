#pragma once

#include "Scenario.hpp"

#include <string>
#include <vector>

constexpr int STRATEGY_SORTING = 0;
constexpr int STRATEGY_GREEDY = 1;
constexpr int STRATEGY_DP = 2;

struct StrategyResult {
    std::string strategyName;
    std::vector<task> selectedTasks;
    int totalStudyTime = -1;
    int totalImportance = -1;
    double executionTime = 0; // milliseconds
    int recommendedStrategyCode = -1; // only used by the AI/ML recommendation result
    std::string comment;
};
