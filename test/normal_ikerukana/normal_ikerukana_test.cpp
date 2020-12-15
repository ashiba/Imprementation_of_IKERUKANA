#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cassert>
#include <queue>
#include <algorithm>
#include <set>

#include "NormalIkerukanaDPSolver.hpp"
#include "NormalIkerukanaSolver.hpp"
#include "CSVLoader.hpp"
#include "gtest/gtest.h"

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

std::vector<std::string> maps_path = {"ktbdmr_map.csv", "generated_30*30map.csv"};


TEST(BFS_SolverTest, zeroDice) {
    const size_t DICE_NUM = 0;
    const size_t MAP_NUM = 24;

    std::vector<int> users_pos;
    int BONBI_data;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[0], users_pos, BONBI_data);
    ASSERT_EQ(Graph.size(), MAP_NUM);

    const std::set<size_t> reachable_node = solver::solveBruteForce(Graph, users_pos[0], DICE_NUM, MAP_NUM);

    std::set<size_t> expected_set = {0};
    ASSERT_EQ(reachable_node, expected_set);
}

TEST(BFS_SolverTest, tenDice) {
    const size_t DICE_NUM = 10;
    const size_t MAP_NUM = 24;

    std::vector<int> users_pos;
    int BONBI_data;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[0], users_pos, BONBI_data);
    ASSERT_EQ(Graph.size(), MAP_NUM);

    const std::set<size_t> reachable_node = solver::solveBruteForce(Graph, users_pos[0], DICE_NUM, MAP_NUM);

    std::set<size_t> expected_set = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 18, 19, 20, 21, 22, 23};
    ASSERT_EQ(reachable_node, expected_set);
}


TEST(IkerukanaAlgorithmTest, DPvsBruteForce) {
    const size_t DICE_NUM = 10;
    const size_t MAP_NUM = 24;

    std::vector<int> users_pos;
    int BONBI_data;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[0], users_pos, BONBI_data);
    ASSERT_EQ(Graph.size(), MAP_NUM);

    const std::set<size_t> reachable_node1 = solver::solveIkerukanaDP(Graph, users_pos[0], DICE_NUM, MAP_NUM);

    const std::set<size_t> reachable_node2 = solver::solveBruteForce(Graph, users_pos[0], DICE_NUM, MAP_NUM);

    ASSERT_EQ(reachable_node1, reachable_node2);
}

TEST(ikerukana_with_BONBI_test, DPExecuteLarge1) {
    const size_t DICE_NUM = 48;
    const size_t MAP_NUM = 30*30;

    std::vector<int> users_pos;
    int BONBI_data;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[1], users_pos, BONBI_data);
    ASSERT_EQ(Graph.size(), MAP_NUM);

    const std::set<size_t> reachable_node1 = solver::solveIkerukanaDP(Graph, users_pos[0], DICE_NUM, MAP_NUM);
}