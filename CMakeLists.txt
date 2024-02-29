cmake_minimum_required(VERSION 3.10)
project(ExpressionSolver VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ExpressionSolver STATIC src/ExpressionSolver.cpp src/Context.cpp)

target_include_directories(ExpressionSolver PUBLIC ${PROJECT_SOURCE_DIR}/include)

enable_testing()
include(CTest)

add_subdirectory(tests)