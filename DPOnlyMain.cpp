#include "Scenario.hpp"
#include "StrategyResult.hpp"

#include <iomanip>
#include <iostream>
#include <vector>

StrategyResult dpStrategy(const std::vector<task>& tasks, int availableStudyTime);

void printScenarioSummary(const scenarioinformation& info) {
    std::cout << "\n=============================================\n";
    std::cout << "DP MODULE TEST EVIDENCE\n";
    std::cout << "=============================================\n";
    std::cout << "Scenario ID      : " << info.scenarioID << '\n';
    std::cout << "Scenario Name    : " << info.scenarioName << '\n';
    std::cout << "Scenario Type    : " << info.scenarioType << '\n';
    std::cout << "Number of Tasks  : " << info.numberOfTasks << '\n';
    std::cout << "Required Time    : " << info.totalRequiredStudyTime << " hours\n";
    std::cout << "Available Time   : " << info.availableStudyTime << " hours\n";
    std::cout << "Pressure Ratio   : "
              << std::fixed << std::setprecision(3)
              << info.timePressureRatio << '\n';
}

void printCompactInputTasks(const std::vector<task>& tasks) {
    std::cout << "\nInput Tasks Used by DP\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "ID    Time   Importance   Task Name\n";
    std::cout << "---------------------------------------------\n";

    for (const task& t : tasks) {
        std::cout << std::left
                  << std::setw(6) << t.taskID
                  << std::setw(7) << t.estimatedStudyTime
                  << std::setw(13) << t.importanceScore
                  << t.taskName << '\n';
    }
}

void printDPSelectedTasks(const StrategyResult& result) {
    std::cout << "\nDP Selected Tasks\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "ID    Time   Importance   Selected Task\n";
    std::cout << "---------------------------------------------\n";

    for (const task& t : result.selectedTasks) {
        std::cout << std::left
                  << std::setw(6) << t.taskID
                  << std::setw(7) << t.estimatedStudyTime
                  << std::setw(13) << t.importanceScore
                  << t.taskName << '\n';
    }

    std::cout << "---------------------------------------------\n";
    std::cout << "Total Study Time Used : "
              << result.totalStudyTime << " hours\n";
    std::cout << "Total Importance Score: "
              << result.totalImportance << '\n';
    std::cout << "Execution Time        : "
              << std::fixed << std::setprecision(6)
              << result.executionTime << " ms\n";
    std::cout << "Comment               : "
              << result.comment << '\n';
}

int main() {
    scenario s;

    // 1 = High Pressure Scenario
    // 2 = Deadline Focused Scenario
    std::vector<int> testScenarios = {1, 2};

    for (int scenarioIndex : testScenarios) {
        scenarioinformation info = s.getScenarioInformation(scenarioIndex);
        const std::vector<task>& tasks = s.getTasks(scenarioIndex);

        printScenarioSummary(info);
        printCompactInputTasks(tasks);

        StrategyResult dpResult =
            dpStrategy(tasks, info.availableStudyTime);

        printDPSelectedTasks(dpResult);
    }

    return 0;
}