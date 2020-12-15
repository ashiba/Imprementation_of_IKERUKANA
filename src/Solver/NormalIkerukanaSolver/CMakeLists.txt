cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME normal_ikerukana_solver)

add_library(${PROJECT_NAME} NormalIkerukanaSolver.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ../)