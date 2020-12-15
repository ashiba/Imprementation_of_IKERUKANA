#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cassert>
#include <queue>
#include <algorithm>
#include <set>
#include <array>

#include "IkerukanaWithBonbiDPSolver.hpp"
#include "IkerukanaWithBonbiSolver.hpp"
#include "CSVLoader.hpp"
#include "gtest/gtest.h"

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

std::vector<std::string> maps_path = {"ktbdmr_map_with_2players.csv", "generated_10*10map.csv", "generated_20*20map.csv"};


TEST(ikerukana_with_BONBI_test, ktbdmr_map_with_2players) {
    const int DICE_NUM = 10;
    const int MAP_NUM = 24;

    std::vector<int> players_pos;
    int BONBI_playser_id;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[0], players_pos, BONBI_playser_id);

    const std::array<std::set<int>, 2> reachable_nodes = solver::solveBruteForce(Graph, players_pos, BONBI_playser_id, DICE_NUM, MAP_NUM);

    const std::array<std::set<int>, 2> reachable_nodes_handmade = {
        std::set<int>{1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 22, 23},
        std::set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 18, 19, 20, 21, 22, 23, 23}
    };

    ASSERT_EQ(reachable_nodes, reachable_nodes_handmade);
}

TEST(ikerukana_with_BONBI_test, DPExecute1) {
    const size_t DICE_NUM = 40;
    const size_t MAP_NUM = 100;

    std::vector<int> users_pos;
    int BONBI_data;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[1], users_pos, BONBI_data);
    ASSERT_EQ(Graph.size(), MAP_NUM);

    const std::array<std::set<int>, 2> reachable_node1 = solver::solveIkerukanaDP(Graph, users_pos, BONBI_data, DICE_NUM, MAP_NUM);
}

TEST(ikerukana_with_BONBI_test, DPExecute2) {
    const size_t DICE_NUM = 40;
    const size_t MAP_NUM = 400;

    std::vector<int> users_pos;
    int BONBI_data;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[2], users_pos, BONBI_data);
    ASSERT_EQ(Graph.size(), MAP_NUM);

    const std::array<std::set<int>, 2> reachable_node1 = solver::solveIkerukanaDP(Graph, users_pos, BONBI_data, DICE_NUM, MAP_NUM);
}

TEST(ikerukana_with_BONBI_test, DPvsBruteForce1) {
    const size_t DICE_NUM = 25;
    const size_t MAP_NUM = 100;

    std::vector<int> users_pos;
    int BONBI_data;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[1], users_pos, BONBI_data);
    ASSERT_EQ(Graph.size(), MAP_NUM);

    const std::array<std::set<int>, 2> reachable_node1 = solver::solveIkerukanaDP(Graph, users_pos, BONBI_data, DICE_NUM, MAP_NUM);
    
    const std::array<std::set<int>, 2> reachable_node2 = solver::solveBruteForce(Graph, users_pos, BONBI_data, DICE_NUM, MAP_NUM);

    ASSERT_EQ(reachable_node1, reachable_node2);
}


TEST(ikerukana_with_BONBI_test, DPvsBruteForce2) {
    const size_t DICE_NUM = 25;
    const size_t MAP_NUM = 400;

    std::vector<int> users_pos;
    int BONBI_data;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[2], users_pos, BONBI_data);
    ASSERT_EQ(Graph.size(), MAP_NUM);

    const std::array<std::set<int>, 2> reachable_node1 = solver::solveIkerukanaDP(Graph, users_pos, BONBI_data, DICE_NUM, MAP_NUM);
    
    const std::array<std::set<int>, 2> reachable_node2 = solver::solveBruteForce(Graph, users_pos, BONBI_data, DICE_NUM, MAP_NUM);

    ASSERT_EQ(reachable_node1, reachable_node2);

    for (int i=0; i<2; ++i) {
        for (const auto& elm: reachable_node1[i]) {
            std::cout << elm << " ";
        }
        std::cout << std::endl;
    }
}
