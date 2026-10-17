#include "StrategyResult.hpp"

#include <vector>

namespace {

int sumStudyTime(
    const std::vector<task>& tasks
) {
    int total = 0;

    for (const task& currentTask : tasks) {
        total += currentTask.estimatedStudyTime;
    }

    return total;
}

int sumImportance(
    const std::vector<task>& tasks
) {
    int total = 0;

    for (const task& currentTask : tasks) {
        total += currentTask.importanceScore;
    }

    return total;
}

// Combines two sorted sections.
// Primary key: earlier deadline.
// Secondary key: higher importance.
void merge(
    std::vector<task>& tasks,
    int left,
    int middle,
    int right
) {
    std::vector<task> leftTasks(
        tasks.begin() + left,
        tasks.begin() + middle + 1
    );

    std::vector<task> rightTasks(
        tasks.begin() + middle + 1,
        tasks.begin() + right + 1
    );

    std::size_t leftIndex = 0;
    std::size_t rightIndex = 0;
    int targetIndex = left;

    while (leftIndex < leftTasks.size() &&
           rightIndex < rightTasks.size()) {
        bool chooseLeft;

        if (leftTasks[leftIndex].deadline !=
            rightTasks[rightIndex].deadline) {
            chooseLeft =
                leftTasks[leftIndex].deadline <
                rightTasks[rightIndex].deadline;
        } else {
            chooseLeft =
                leftTasks[leftIndex].importanceScore >=
                rightTasks[rightIndex].importanceScore;
        }

        if (chooseLeft) {
            tasks[targetIndex] =
                leftTasks[leftIndex];

            ++leftIndex;
        } else {
            tasks[targetIndex] =
                rightTasks[rightIndex];

            ++rightIndex;
        }

        ++targetIndex;
    }

    while (leftIndex < leftTasks.size()) {
        tasks[targetIndex] =
            leftTasks[leftIndex];

        ++leftIndex;
        ++targetIndex;
    }

    while (rightIndex < rightTasks.size()) {
        tasks[targetIndex] =
            rightTasks[rightIndex];

        ++rightIndex;
        ++targetIndex;
    }
}

void mergeSort(
    std::vector<task>& tasks,
    int left,
    int right
) {
    if (left >= right) {
        return;
    }

    const int middle =
        left + (right - left) / 2;

    mergeSort(tasks, left, middle);
    mergeSort(tasks, middle + 1, right);

    merge(tasks, left, middle, right);
}

}  // namespace

StrategyResult mergeSortStrategy(
    const std::vector<task>& tasks,
    int availableStudyTime
) {
    // The original task list is not modified.
    std::vector<task> sortedTasks = tasks;

    if (!sortedTasks.empty()) {
        mergeSort(
            sortedTasks,
            0,
            static_cast<int>(
                sortedTasks.size()
            ) - 1
        );
    }

    StrategyResult result{};

    result.strategyName =
        "Sorting-based ranking (Merge Sort)";

    int usedTime = 0;

    for (const task& currentTask : sortedTasks) {
        if (usedTime +
                currentTask.estimatedStudyTime <=
            availableStudyTime) {
            result.selectedTasks.push_back(
                currentTask
            );

            usedTime +=
                currentTask.estimatedStudyTime;
        }
    }

    result.totalStudyTime =
        sumStudyTime(result.selectedTasks);

    result.totalImportance =
        sumImportance(result.selectedTasks);

    // Execution time is measured centrally in main.cpp.
    result.executionTime = 0.0;

    result.comment =
        "Uses Merge Sort to rank tasks by earliest "
        "deadline first, then by higher importance. "
        "Tasks are selected from the ranking while "
        "staying within the available study time.";

    return result;
}