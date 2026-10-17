#include "Scenario.hpp"
#include "StrategyResult.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

StrategyResult predictStrategy(
    const scenarioinformation& info
);

StrategyResult mergeSortStrategy(
    const std::vector<task>& tasks,
    int availableStudyTime
);

StrategyResult greedySortStrategy(
    const std::vector<task>& tasks,
    int availableStudyTime
);

StrategyResult dpStrategy(
    const std::vector<task>& tasks,
    int availableStudyTime
);

namespace {

constexpr int BENCHMARK_REPETITIONS = 10000;
constexpr int BENCHMARK_WARMUP_RUNS = 100;

}  // namespace

template <typename Callable>
double benchmarkAverageMilliseconds(
    Callable&& callable,
    int repetitions = BENCHMARK_REPETITIONS,
    int warmupRuns = BENCHMARK_WARMUP_RUNS
) {
    volatile long long benchmarkSink = 0;

    // Warm-up runs reduce first-run effects.
    for (int i = 0; i < warmupRuns; ++i) {
        const StrategyResult result =
            callable();

        benchmarkSink += result.totalImportance;
        benchmarkSink += result.totalStudyTime;
        benchmarkSink +=
            result.recommendedStrategyCode;

        benchmarkSink +=
            static_cast<long long>(
                result.selectedTasks.size()
            );
    }

    const auto startTime =
        std::chrono::steady_clock::now();

    for (int i = 0; i < repetitions; ++i) {
        const StrategyResult result =
            callable();

        benchmarkSink += result.totalImportance;
        benchmarkSink += result.totalStudyTime;
        benchmarkSink +=
            result.recommendedStrategyCode;

        benchmarkSink +=
            static_cast<long long>(
                result.selectedTasks.size()
            );
    }

    const auto endTime =
        std::chrono::steady_clock::now();

    const double totalMilliseconds =
        std::chrono::duration<
            double,
            std::milli
        >(endTime - startTime).count();

    // Prevents the benchmark calls from being
    // removed as unused work.
    (void)benchmarkSink;

    return totalMilliseconds / repetitions;
}

std::string strategyCodeToString(
    int strategyCode
) {
    switch (strategyCode) {
        case STRATEGY_SORTING:
            return "Sorting-based ranking";

        case STRATEGY_GREEDY:
            return "Greedy strategy";

        case STRATEGY_DP:
            return "Dynamic Programming";

        default:
            return "Unknown strategy";
    }
}

std::string selectedTaskIDsToString(
    const std::vector<task>& selectedTasks
) {
    if (selectedTasks.empty()) {
        return "-";
    }

    std::ostringstream output;

    for (std::size_t i = 0;
         i < selectedTasks.size();
         ++i) {
        if (i > 0) {
            output << ", ";
        }

        output << selectedTasks[i].taskID;
    }

    return output.str();
}

std::string numberOrDash(
    double value,
    int precision = 6
) {
    if (value < 0) {
        return "-";
    }

    std::ostringstream output;

    output << std::fixed
           << std::setprecision(precision)
           << value;

    return output.str();
}

std::string numberOrDash(int value) {
    if (value < 0) {
        return "-";
    }

    return std::to_string(value);
}

bool isResultFeasible(
    const StrategyResult& result,
    int availableStudyTime
) {
    return result.totalStudyTime >= 0 &&
           result.totalStudyTime <=
               availableStudyTime;
}

void printScenarioSummary(
    const scenarioinformation& info
) {
    std::cout << "\nScenario information\n";
    std::cout
        << "--------------------------------------------------\n";

    std::cout
        << "Scenario ID: "
        << info.scenarioID << '\n';

    std::cout
        << "Scenario name: "
        << info.scenarioName << '\n';

    std::cout
        << "Scenario type: "
        << info.scenarioType << '\n';

    std::cout
        << "Number of tasks: "
        << info.numberOfTasks << '\n';

    std::cout
        << "Total required study time: "
        << info.totalRequiredStudyTime
        << " hours\n";

    std::cout
        << "Available study time: "
        << info.availableStudyTime
        << " hours\n";

    std::cout
        << "Time pressure ratio: "
        << std::fixed
        << std::setprecision(3)
        << info.timePressureRatio
        << '\n';

    std::cout
        << "Average importance: "
        << std::fixed
        << std::setprecision(2)
        << info.averageImportance
        << '\n';

    std::cout
        << "Deadline tightness: "
        << std::fixed
        << std::setprecision(3)
        << info.deadlineTightness
        << '\n';

    std::cout
        << "Importance variation: "
        << std::fixed
        << std::setprecision(3)
        << info.importanceVariation
        << '\n';
}

void printTaskTable(
    const std::vector<task>& tasks
) {
    std::cout << "\nStudy tasks\n";
    std::cout
        << "--------------------------------------------------\n";

    std::cout
        << std::left
        << std::setw(6) << "ID"
        << std::setw(34) << "Task"
        << std::setw(8) << "Time"
        << std::setw(12) << "Importance"
        << std::setw(10) << "Deadline"
        << std::setw(12) << "Difficulty"
        << "Type\n";

    for (const task& currentTask : tasks) {
        std::cout
            << std::left
            << std::setw(6)
            << currentTask.taskID

            << std::setw(34)
            << currentTask.taskName

            << std::setw(8)
            << currentTask.estimatedStudyTime

            << std::setw(12)
            << currentTask.importanceScore

            << std::setw(10)
            << currentTask.deadline

            << std::setw(12)
            << currentTask.difficultyLevel

            << currentTask.taskType
            << '\n';
    }
}

void printResultBlock(
    const StrategyResult& result
) {
    std::cout
        << "\nStrategy: "
        << result.strategyName
        << '\n';

    std::cout
        << "Selected Tasks: "
        << selectedTaskIDsToString(
               result.selectedTasks
           )
        << '\n';

    std::cout
        << "Total Study Time: "
        << numberOrDash(
               result.totalStudyTime
           )
        << '\n';

    std::cout
        << "Total Importance: "
        << numberOrDash(
               result.totalImportance
           )
        << '\n';

    std::cout
        << "Average Execution Time: "
        << numberOrDash(
               result.executionTime,
               6
           )
        << " ms\n";

    std::cout
        << "Comment: "
        << (
               result.comment.empty()
                   ? "-"
                   : result.comment
           )
        << '\n';
}

void printComparisonTable(
    const StrategyResult& sortingResult,
    const StrategyResult& greedyResult,
    const StrategyResult& dpResult,
    const StrategyResult& aiComparisonResult
) {
    std::cout
        << "\nStrategy performance comparison\n";

    std::cout
        << "--------------------------------------------------";

    printResultBlock(sortingResult);
    printResultBlock(greedyResult);
    printResultBlock(dpResult);
    printResultBlock(aiComparisonResult);
}

const StrategyResult& findBestFeasibleResult(
    const StrategyResult& sortingResult,
    const StrategyResult& greedyResult,
    const StrategyResult& dpResult,
    int availableStudyTime
) {
    const StrategyResult* bestResult = nullptr;

    const auto consider =
        [&](const StrategyResult& candidate) {
            if (!isResultFeasible(
                    candidate,
                    availableStudyTime
                )) {
                return;
            }

            if (
                bestResult == nullptr ||

                candidate.totalImportance >
                    bestResult->totalImportance ||

                (
                    candidate.totalImportance ==
                        bestResult->totalImportance &&

                    candidate.totalStudyTime <
                        bestResult->totalStudyTime
                ) ||

                (
                    candidate.totalImportance ==
                        bestResult->totalImportance &&

                    candidate.totalStudyTime ==
                        bestResult->totalStudyTime &&

                    candidate.executionTime <
                        bestResult->executionTime
                )
            ) {
                bestResult = &candidate;
            }
        };

    consider(sortingResult);
    consider(greedyResult);
    consider(dpResult);

    if (bestResult == nullptr) {
        return sortingResult;
    }

    return *bestResult;
}

const StrategyResult&
getRecommendedAlgorithmResult(
    const StrategyResult& sortingResult,
    const StrategyResult& greedyResult,
    const StrategyResult& dpResult,
    const StrategyResult& aiResult
) {
    if (
        aiResult.recommendedStrategyCode ==
        STRATEGY_GREEDY
    ) {
        return greedyResult;
    }

    if (
        aiResult.recommendedStrategyCode ==
        STRATEGY_DP
    ) {
        return dpResult;
    }

    return sortingResult;
}

StrategyResult buildAIComparisonResult(
    const StrategyResult&
        recommendedAlgorithmResult,

    const StrategyResult& aiResult
) {
    StrategyResult aiComparison =
        recommendedAlgorithmResult;

    aiComparison.strategyName =
        "AI/ML Recommendation (" +
        strategyCodeToString(
            aiResult.recommendedStrategyCode
        ) +
        ")";

    // AI workflow time =
    // prediction time + chosen algorithm time.
    aiComparison.executionTime =
        aiResult.executionTime +
        recommendedAlgorithmResult.executionTime;

    aiComparison.comment =
        aiResult.comment +
        " The AI/ML module recommends using " +
        recommendedAlgorithmResult.strategyName +
        ". The reported time includes prediction "
        "and recommended-strategy execution.";

    return aiComparison;
}

void printPerformanceMeasurementSettings() {
    std::cout
        << "\nPerformance measurement settings\n";

    std::cout
        << "--------------------------------------------------\n";

    std::cout
        << "Clock: std::chrono::steady_clock\n";

    std::cout
        << "Warm-up runs: "
        << BENCHMARK_WARMUP_RUNS
        << '\n';

    std::cout
        << "Measured repetitions: "
        << BENCHMARK_REPETITIONS
        << '\n';

    std::cout
        << "Reported value: average execution "
        << "time per run\n";
}

void printFinalEvaluation(
    const StrategyResult& bestResult,

    const StrategyResult&
        recommendedAlgorithmResult,

    const StrategyResult& aiResult,

    const scenarioinformation& info
) {
    std::cout
        << "\nFinal evaluation "
        << "(Available study time: "
        << info.availableStudyTime
        << " hours)\n";

    std::cout
        << "--------------------------------------------------\n";

    std::cout
        << "Best observed strategy based on total "
        << "importance, study time, and average "
        << "execution time: "
        << bestResult.strategyName
        << '\n';

    std::cout
        << "Best observed total time: "
        << numberOrDash(
               bestResult.totalStudyTime
           )
        << " hours\n";

    std::cout
        << "Best observed total importance: "
        << numberOrDash(
               bestResult.totalImportance
           )
        << '\n';

    std::cout
        << "Best observed average execution time: "
        << numberOrDash(
               bestResult.executionTime,
               6
           )
        << " ms\n";

    std::cout
        << "\nAI recommended algorithm: "
        << strategyCodeToString(
               aiResult.recommendedStrategyCode
           )
        << '\n';

    std::cout
        << "Recommended algorithm total time: "
        << numberOrDash(
               recommendedAlgorithmResult
                   .totalStudyTime
           )
        << " hours\n";

    std::cout
        << "Recommended algorithm total importance: "
        << numberOrDash(
               recommendedAlgorithmResult
                   .totalImportance
           )
        << '\n';

    std::cout
        << "Recommended algorithm average "
        << "execution time: "
        << numberOrDash(
               recommendedAlgorithmResult
                   .executionTime,
               6
           )
        << " ms\n";

    const bool recommendationIsFeasible =
        isResultFeasible(
            recommendedAlgorithmResult,
            info.availableStudyTime
        );

    const bool achievesBestObservedImportance =
        recommendedAlgorithmResult
            .totalImportance ==
        bestResult.totalImportance;

    if (
        recommendationIsFeasible &&
        achievesBestObservedImportance
    ) {
        std::cout
            << "Evaluation: The AI-recommended "
            << "strategy achieves the highest observed "
            << "total importance without exceeding the "
            << "available study time.\n";
    } else {
        std::cout
            << "Evaluation: The AI-recommended "
            << "strategy does not achieve the highest "
            << "observed total importance for this "
            << "scenario.\n";
    }
}

int main() {
    scenario scenarioManager;

    char choice;

    while (true) {
        std::cout
            << "Select a scenario:\n"
            << "  0: Low Pressure\n"
            << "  1: High Pressure\n"
            << "  2: Deadline Focused\n"
            << "  3: Importance Focused\n"
            << "Your choice [0-3]: ";

        if (
            std::cin >> choice &&
            choice >= '0' &&
            choice <= '3'
        ) {
            break;
        }

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<
                std::streamsize
            >::max(),
            '\n'
        );

        std::cout
            << "Invalid input, please try again.\n\n";
    }

    const int scenarioIndex =
        choice - '0';

    const scenarioinformation info =
        scenarioManager
            .getScenarioInformation(
                scenarioIndex
            );

    const std::vector<task>& tasks =
        scenarioManager.getTasks(
            scenarioIndex
        );

    printScenarioSummary(info);
    printTaskTable(tasks);

    // Run once to obtain the actual result.
    StrategyResult sortingResult =
        mergeSortStrategy(
            tasks,
            info.availableStudyTime
        );

    StrategyResult greedyResult =
        greedySortStrategy(
            tasks,
            info.availableStudyTime
        );

    StrategyResult dpResult =
        dpStrategy(
            tasks,
            info.availableStudyTime
        );

    StrategyResult aiResult =
        predictStrategy(info);

    // Measure every strategy using the same clock,
    // scope, warm-up count, and repetition count.
    sortingResult.executionTime =
        benchmarkAverageMilliseconds(
            [&]() {
                return mergeSortStrategy(
                    tasks,
                    info.availableStudyTime
                );
            }
        );

    greedyResult.executionTime =
        benchmarkAverageMilliseconds(
            [&]() {
                return greedySortStrategy(
                    tasks,
                    info.availableStudyTime
                );
            }
        );

    dpResult.executionTime =
        benchmarkAverageMilliseconds(
            [&]() {
                return dpStrategy(
                    tasks,
                    info.availableStudyTime
                );
            }
        );

    aiResult.executionTime =
        benchmarkAverageMilliseconds(
            [&]() {
                return predictStrategy(info);
            }
        );

    printPerformanceMeasurementSettings();

    std::cout
        << "\nAI recommended algorithm: "
        << strategyCodeToString(
               aiResult.recommendedStrategyCode
           )
        << '\n';

    std::cout
        << "AI comment: "
        << aiResult.comment
        << '\n';

    const StrategyResult&
        recommendedAlgorithmResult =
            getRecommendedAlgorithmResult(
                sortingResult,
                greedyResult,
                dpResult,
                aiResult
            );

    const StrategyResult aiComparisonResult =
        buildAIComparisonResult(
            recommendedAlgorithmResult,
            aiResult
        );

    printComparisonTable(
        sortingResult,
        greedyResult,
        dpResult,
        aiComparisonResult
    );

    const StrategyResult& bestResult =
        findBestFeasibleResult(
            sortingResult,
            greedyResult,
            dpResult,
            info.availableStudyTime
        );

    printFinalEvaluation(
        bestResult,
        recommendedAlgorithmResult,
        aiResult,
        info
    );

    return 0;
}
