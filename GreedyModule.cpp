#include "StrategyResult.hpp"

#include <algorithm>
#include <vector>

// Utility function: calculate total study time of a task list
namespace {

int calculateTotalStudyTime(
    const std::vector<task>& tasks
) {
    int total = 0;

    // Sum up estimated study time for all tasks
    for (const task& currentTask : tasks) {
        total += currentTask.estimatedStudyTime;
    }

    return total;
}

// Utility function: calculate total importance score of a task list
int calculateTotalImportance(
    const std::vector<task>& tasks
) {
    int total = 0;

    // Sum up importance scores for all tasks
    for (const task& currentTask : tasks) {
        total += currentTask.importanceScore;
    }

    return total;
}

}  // namespace

// Greedy strategy: select tasks based on importance-to-time ratio
StrategyResult greedySortStrategy(
    const std::vector<task>& tasks,
    int availableStudyTime
) {
    // Create a copy of tasks for sorting (do not modify original input)
    std::vector<task> sortedTasks = tasks;

    // Sort tasks in descending order of importance / time ratio
    std::sort(
        sortedTasks.begin(),
        sortedTasks.end(),
        [](const task& a, const task& b) {
            const double ratioA =
                static_cast<double>(
                    a.importanceScore
                ) /
                a.estimatedStudyTime;

            const double ratioB =
                static_cast<double>(
                    b.importanceScore
                ) /
                b.estimatedStudyTime;

            // Higher ratio gets higher priority
            return ratioA > ratioB;
        }
    );

    StrategyResult result{};
    result.strategyName = "Greedy Strategy";

    int currentUsedTime = 0;

    // Select tasks greedily until time limit is reached
    for (const task& currentTask : sortedTasks) {
        if (currentUsedTime +
                currentTask.estimatedStudyTime <=
            availableStudyTime) {

            // Add task to selected list
            result.selectedTasks.push_back(
                currentTask
            );

            // Update used time
            currentUsedTime +=
                currentTask.estimatedStudyTime;
        }
    }

    // Compute total study time of selected tasks
    result.totalStudyTime =
        calculateTotalStudyTime(
            result.selectedTasks
        );

    // Compute total importance of selected tasks
    result.totalImportance =
        calculateTotalImportance(
            result.selectedTasks
        );

    // Execution time is measured centrally in main.cpp.
    result.executionTime = 0.0;

    // Explanation of strategy behavior
    result.comment =
        "Uses Greedy strategy: prioritizing tasks "
        "with the highest importance-to-time ratio.";

    return result;
}