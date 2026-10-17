#include "Scenario.hpp"

#include <cmath>

scenario::scenario() {
    initializeScenarios();
}

void scenario::initializeScenarios() {
    scenarios.clear();

    scenarios.push_back({
        "S1",
        "Low Pressure Scenario 1",
        "low_pressure",
        36,
        {
            {"T1", "Review Sorting Algorithms", 2, 4, 5, 2, "revision"},
            {"T2", "Revise Dynamic Programming", 3, 5, 7, 4, "revision"},
            {"T3", "Complete Graph Tutorial", 2, 4, 4, 3, "tutorial"},
            {"T4", "Finish Assignment Draft", 4, 5, 6, 4, "assignment"},
            {"T5", "Watch Greedy Lecture", 1, 3, 8, 2, "lecture"},
            {"T6", "Practice Knapsack Problems", 3, 5, 9, 4, "practice"},
            {"T7", "Revise Divide and Conquer", 2, 4, 5, 3, "revision"},
            {"T8", "Prepare Quiz Notes", 3, 3, 10, 2, "revision"},
            {"T9", "Complete Recursion Exercises", 4, 4, 11, 3, "practice"},
            {"T10", "Review Complexity Analysis", 2, 5, 6, 3, "revision"},
            {"T11", "Summarize Lecture Notes", 2, 3, 9, 2, "revision"},
            {"T12", "Solve Practice Set A", 3, 4, 12, 3, "practice"},
            {"T13", "Watch BFS and DFS Video", 2, 3, 10, 2, "lecture"},
            {"T14", "Complete Tutorial Sheet 2", 3, 4, 8, 3, "tutorial"},
            {"T15", "Read Textbook Chapter 5", 2, 3, 13, 2, "lecture"}
        }
    });

    scenarios.push_back({
        "S2",
        "High Pressure Scenario 1",
        "high_pressure",
        12,
        {
            {"T1", "Complete Final Assignment", 5, 5, 2, 5, "assignment"},
            {"T2", "Revise Dynamic Programming", 4, 5, 4, 5, "revision"},
            {"T3", "Practice Graph Algorithms", 6, 5, 5, 5, "practice"},
            {"T4", "Review Sorting Algorithms", 3, 4, 5, 3, "revision"},
            {"T5", "Complete Greedy Tutorial", 4, 4, 4, 4, "tutorial"},
            {"T6", "Study Divide and Conquer", 5, 4, 6, 4, "revision"},
            {"T7", "Watch Complexity Lecture", 2, 3, 7, 2, "lecture"},
            {"T8", "Practice Recursion Problems", 3, 3, 5, 3, "practice"},
            {"T9", "Review Past Year Questions", 4, 5, 4, 4, "practice"},
            {"T10", "Prepare Exam Summary", 5, 4, 5, 4, "revision"},
            {"T11", "Attempt Mock Exam Paper 1", 5, 5, 3, 5, "practice"},
            {"T12", "Complete Lab Report", 4, 4, 3, 4, "assignment"},
            {"T13", "Revise Hashing Topics", 4, 4, 4, 4, "revision"},
            {"T14", "Practice Tree Problems", 5, 5, 5, 5, "practice"},
            {"T15", "Prepare Group Presentation", 4, 4, 6, 4, "assignment"}
        }
    });

    scenarios.push_back({
        "S3",
        "Deadline Focused Scenario 1",
        "deadline_focused",
        22,
        {
            {"T1", "Submit Algorithm Assignment", 4, 5, 1, 4, "assignment"},
            {"T2", "Complete Graph Tutorial", 3, 4, 1, 3, "tutorial"},
            {"T3", "Revise DP Quiz Topics", 3, 5, 2, 4, "revision"},
            {"T4", "Practice Greedy Problems", 2, 3, 2, 3, "practice"},
            {"T5", "Watch Sorting Lecture", 1, 2, 1, 2, "lecture"},
            {"T6", "Review Complexity Notes", 2, 4, 3, 3, "revision"},
            {"T7", "Prepare Presentation Slides", 4, 4, 2, 3, "assignment"},
            {"T8", "Complete Recursion Worksheet", 3, 3, 4, 3, "tutorial"},
            {"T9", "Read Backtracking Notes", 2, 3, 5, 4, "lecture"},
            {"T10", "Solve Knapsack Exercises", 4, 5, 3, 5, "practice"},
            {"T11", "Submit Lab Worksheet", 2, 4, 1, 3, "assignment"},
            {"T12", "Finish Quiz Revision", 3, 4, 2, 3, "revision"},
            {"T13", "Complete Online Test", 2, 3, 1, 2, "tutorial"},
            {"T14", "Practice DP Problem Set", 3, 4, 5, 4, "practice"},
            {"T15", "Read Graph Theory Notes", 2, 3, 6, 3, "lecture"}
        }
    });

    scenarios.push_back({   
        "S4",
        "Importance Focused Scenario 1",
        "importance_focused",
        20,
        {
            {"T1", "Revise Dynamic Programming", 4, 5, 5, 5, "revision"},
            {"T2", "Practice Knapsack Problems", 3, 5, 6, 4, "practice"},
            {"T3", "Complete Graph Assignment", 5, 5, 4, 5, "assignment"},
            {"T4", "Review Complexity Proofs", 2, 5, 8, 3, "revision"},
            {"T5", "Watch Introductory Lecture", 1, 1, 7, 1, "lecture"},
            {"T6", "Practice Basic Sorting", 2, 1, 9, 2, "practice"},
            {"T7", "Read Optional Notes", 3, 1, 10, 2, "lecture"},
            {"T8", "Complete Tutorial Corrections", 2, 2, 6, 2, "tutorial"},
            {"T9", "Review Greedy Examples", 3, 5, 5, 3, "revision"},
            {"T10", "Prepare Exam Formula Sheet", 2, 5, 3, 2, "revision"},
            {"T11", "Final Project Submission", 4, 5, 5, 5, "assignment"},
            {"T12", "Browse Reference Material", 2, 1, 9, 1, "lecture"},
            {"T13", "Organize Study Folder", 1, 1, 10, 1, "revision"},
            {"T14", "Skim Extra Readings", 2, 2, 8, 1, "lecture"},
            {"T15", "Critical Exam Revision", 3, 5, 4, 4, "revision"}
        }
    });
}


const std::vector<task>& scenario::getTasks(int scenarioIndex) const {
    return scenarios[scenarioIndex].tasks;
}

scenarioinformation scenario::getScenarioInformation(int scenarioIndex) const {
    const scenariodata& data = scenarios[scenarioIndex];
    const std::vector<task>& tasks = data.tasks;

    scenarioinformation info{};
    info.numberOfTasks = static_cast<int>(tasks.size());
    info.availableStudyTime = data.availableStudyTime;

    if (tasks.empty()) {
        return info;
    }

    int totalImportance = 0;
    int urgentTaskCount = 0;

    for (const task& currentTask : tasks) {
        info.totalRequiredStudyTime += currentTask.estimatedStudyTime;
        totalImportance += currentTask.importanceScore;

        if (currentTask.deadline <= 2) {
            ++urgentTaskCount;
        }
    }

    if (info.availableStudyTime > 0) {
        info.timePressureRatio =
            static_cast<double>(info.totalRequiredStudyTime) /
            info.availableStudyTime;
    }

    info.averageImportance =
        static_cast<double>(totalImportance) / info.numberOfTasks;

    // Deadline tightness uses the ratio of urgent tasks. A task is urgent when
    // its deadline is within 2 days.
    info.deadlineTightness =
        static_cast<double>(urgentTaskCount) / info.numberOfTasks;

    double squaredDifferenceSum = 0.0;
    for (const task& currentTask : tasks) {
        const double difference =
            currentTask.importanceScore - info.averageImportance;
        squaredDifferenceSum += difference * difference;
    }

    const double variance = squaredDifferenceSum / info.numberOfTasks;
    info.importanceVariation = std::sqrt(variance);

    info.scenarioID = data.scenarioID;
    info.scenarioName = data.scenarioName;
    info.scenarioType = data.scenarioType;

    return info;
}
