cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME ikerukana_with_bonbi_dp_solver)

add_library(${PROJECT_NAME} IkerukanaWithBonbiDPSolver.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ../)