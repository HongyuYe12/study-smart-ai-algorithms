#include "Scenario.hpp"
#include "StrategyResult.hpp"

// Predict the recommended strategy based on scenario information
StrategyResult predictStrategy(
    const scenarioinformation& info
) {
    StrategyResult result{};

    // Case 1: Very high time pressure (>= 1.5)
    // Use Dynamic Programming to achieve optimal global selection
    if (info.timePressureRatio >= 1.5) {
        result.recommendedStrategyCode =
            STRATEGY_DP;

        result.strategyName =
            "Dynamic Programming";

        result.comment =
            "High pressure or tight schedule "
            "requires optimal selection.";
    } 
    // Case 2: Tight deadline constraint (>= 0.4)
    // Use Greedy Strategy for fast prioritization
    else if (info.deadlineTightness >= 0.4) {
        result.recommendedStrategyCode =
            STRATEGY_GREEDY;

        result.strategyName =
            "Greedy Strategy";

        result.comment =
            "Urgent deadlines require "
            "prioritization.";
    } 
    // Case 3: High importance variation and moderate time pressure
    // Use Greedy Strategy with heuristic selection
    else if (
        info.importanceVariation >= 0.8 &&
        info.timePressureRatio <= 2.2
    ) {
        result.recommendedStrategyCode =
            STRATEGY_GREEDY;

        result.strategyName =
            "Greedy Strategy";

        result.comment =
            "High variability benefits from "
            "heuristic selection.";
    } 
    // Case 4: Default case
    // Use sorting-based ranking for basic prioritization
    else {
        result.recommendedStrategyCode =
            STRATEGY_SORTING;

        result.strategyName =
            "Sorting-based ranking";

        result.comment =
            "Low pressure scenarios focus on "
            "task prioritization.";
    }

    return result;
}