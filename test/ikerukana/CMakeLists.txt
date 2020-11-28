cmake_minimum_required(VERSION 3.1)

set(PROJECT_NAME run_ikerukana_test)
set(TOPDIR ../..)

add_executable(${PROJECT_NAME} ikerukana_test.cpp)

find_package(GTest REQUIRED COFNIG)
if (GTest_FOUND)
    target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
endif(GTest_FOUND)

# target_link_libraries(${PROJECT_NAME} ikerukana)
# target_include_directories(${PROJECT_NAME} ${TOPDIR}/src/)
