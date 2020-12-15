cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME normal_ikerukana_dp_solver)

add_library(${PROJECT_NAME} NormalIkerukanaDPSolver.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ../)