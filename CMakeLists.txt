cmake_minimum_required(VERSION 3.16)
project(StudySmartAI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(study_smart_ai
    main.cpp
    Scenario.cpp
    PredictStrategy.cpp
    SortingModule.cpp
    GreedyModule.cpp
    DPModule.cpp
)

add_executable(dp_demo
    DPOnlyMain.cpp
    Scenario.cpp
    DPModule.cpp
)
