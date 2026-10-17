#pragma once

#include <string>
#include <vector>

struct task {
    std::string taskID;
    std::string taskName;
    int estimatedStudyTime; // hours
    int importanceScore;    // 1-5
    int deadline;           // days remaining
    int difficultyLevel;    // 1-5
    std::string taskType;
};

struct scenarioinformation {
    std::string scenarioID;
    std::string scenarioName;
    std::string scenarioType;

    int numberOfTasks;
    int totalRequiredStudyTime;
    int availableStudyTime;
    double timePressureRatio;   // 0 - 无限大。> 1 表示所需时间超过可用时间（压力大），< 1 表示可用时间充裕。值越大 压力越大。
    double averageImportance;  // 1 - 5

    double deadlineTightness; // 0 - 1，表示截止日期在两天内的任务站所有任务的百分比。

    double importanceVariation; // 标准差， 范围是 0 - 2。
};

class scenario {
private:
    struct scenariodata {
        std::string scenarioID;
        std::string scenarioName;
        std::string scenarioType;
        int availableStudyTime;
        std::vector<task> tasks;
    };

    std::vector<scenariodata> scenarios;

    void initializeScenarios();

public:
    scenario();

    // Generate the four hard-coded project scenarios.

    const std::vector<task>& getTasks(int scenarioIndex) const;

    // Return the required scenario features for AI/ML strategy prediction.
    scenarioinformation getScenarioInformation(int scenarioIndex) const;
};
