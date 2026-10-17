# Study Smart AI — Algorithm Strategy Comparison

A C++17 project comparing three approaches to prioritizing study tasks under a fixed time budget:

- sorting-based ranking;
- greedy selection using an importance-to-time ratio;
- dynamic programming using a 0/1 knapsack formulation.

The program evaluates predefined workload scenarios, benchmarks each strategy, and recommends an approach based on scenario characteristics.

## Highlights

- Modular sorting, greedy, and dynamic-programming implementations
- Task modelling with importance, time, deadline, difficulty, and type
- Feasibility and result-quality comparison across strategies
- Repeatable micro-benchmarking with warm-up runs
- A separate focused dynamic-programming demonstration

## Build

```bash
cmake -S . -B build
cmake --build build
```

Run the main comparison program:

```bash
./build/study_smart_ai
```

Run the focused DP demonstration:

```bash
./build/dp_demo
```

On multi-configuration generators such as Visual Studio, executables may be under `build/Debug` or `build/Release`.

## Project Structure

- `main.cpp` — interactive comparison and benchmarking
- `SortingModule.cpp` — merge-sort-based ranking
- `GreedyModule.cpp` — ratio-based greedy selection
- `DPModule.cpp` — 0/1 knapsack optimization
- `PredictStrategy.cpp` — rule-based strategy recommendation
- `Scenario.cpp` — scenario and task data
- `DPOnlyMain.cpp` — focused DP demonstration

## Verification

Both executable targets were compiled successfully with GCC 16.1 using `-std=c++17 -Wall -Wextra -pedantic` before publication.

## Context

This is a cleaned portfolio version of a completed university coursework project. Assessment sheets, course instructions, personal identifiers, compiled binaries, and submission artifacts are intentionally excluded.
