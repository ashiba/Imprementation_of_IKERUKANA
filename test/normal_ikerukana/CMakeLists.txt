cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME run_normal_ikerukana_test)
set(TOPDIR ../..)

set(CMAKE_CXX_FLAGS "-O2 -Wall -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")


get_filename_component(MAPS_ABSOLUTE_PATH "${TOPDIR}/maps/" ABSOLUTE)
add_definitions(-D MAPS_DIR=${MAPS_ABSOLUTE_PATH})
message(STATUS ${MAPS_ABSOLUTE_PATH})

add_executable(${PROJECT_NAME} normal_ikerukana_test.cpp)

find_package(GTest REQUIRED CONFIG)
if (GTest_FOUND)
    target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
endif(GTest_FOUND)

target_link_libraries(${PROJECT_NAME} ikerukana_dp_solver csv_loader)
target_include_directories(${PROJECT_NAME} PRIVATE ${TOPDIR}/src/Solver ${TOPDIR}/src/Library)

add_subdirectory(${TOPDIR}/src/Solver Solver)
add_subdirectory(${TOPDIR}/src/Library csv_loader)