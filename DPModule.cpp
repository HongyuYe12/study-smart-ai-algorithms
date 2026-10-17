#include "StrategyResult.hpp"

#include <algorithm>
#include <vector>

namespace {

int calculateTotalStudyTime(const std::vector<task>& selectedTasks) {
    int total = 0;

    for (const task& currentTask : selectedTasks) {
        total += currentTask.estimatedStudyTime;
    }

    return total;
}

int calculateTotalImportance(const std::vector<task>& selectedTasks) {
    int total = 0;

    for (const task& currentTask : selectedTasks) {
        total += currentTask.importanceScore;
    }

    return total;
}

}  // namespace

StrategyResult dpStrategy(const std::vector<task>& tasks,
                          int availableStudyTime) {
    const int taskCount = static_cast<int>(tasks.size());

    std::vector<std::vector<int>> dp(
        taskCount + 1,
        std::vector<int>(availableStudyTime + 1, 0)
    );

    for (int i = 1; i <= taskCount; ++i) {
        const int studyTime =
            tasks[i - 1].estimatedStudyTime;

        const int importance =
            tasks[i - 1].importanceScore;

        for (int time = 0;
             time <= availableStudyTime;
             ++time) {
            dp[i][time] = dp[i - 1][time];

            if (studyTime <= time) {
                dp[i][time] = std::max(
                    dp[i][time],
                    dp[i - 1][time - studyTime] +
                        importance
                );
            }
        }
    }

    StrategyResult result{};
    result.strategyName = "Dynamic Programming";

    int remainingTime = availableStudyTime;

    for (int i = taskCount; i >= 1; --i) {
        if (dp[i][remainingTime] !=
            dp[i - 1][remainingTime]) {
            result.selectedTasks.push_back(
                tasks[i - 1]
            );

            remainingTime -=
                tasks[i - 1].estimatedStudyTime;
        }
    }

    std::reverse(
        result.selectedTasks.begin(),
        result.selectedTasks.end()
    );

    result.totalStudyTime =
        calculateTotalStudyTime(
            result.selectedTasks
        );

    result.totalImportance =
        calculateTotalImportance(
            result.selectedTasks
        );

    // Execution time is measured centrally in main.cpp.
    result.executionTime = 0.0;

    result.comment =
        "Uses 0/1 Knapsack Dynamic Programming to "
        "maximize total importance without exceeding "
        "the available study time.";

    return result;
}
