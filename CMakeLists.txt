cmake_minimum_required(VERSION 3.16)
project(StudySmartAI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(study_smart_ai
    src/main.cpp
    src/Scenario.cpp
    src/PredictStrategy.cpp
    src/SortingModule.cpp
    src/GreedyModule.cpp
    src/DPModule.cpp
)

target_include_directories(study_smart_ai PRIVATE src)

add_executable(dp_demo
    src/DPOnlyMain.cpp
    src/Scenario.cpp
    src/DPModule.cpp
)

target_include_directories(dp_demo PRIVATE src)

