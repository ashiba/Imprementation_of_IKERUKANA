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

std::vector<std::string> maps_path = {"ktbdmr_map_with_2players.csv"};


TEST(ikerukana_with_BONBI_test, ktbdmr_map_with_2players) {
    const int DICE_NUM = 10;
    const int MAP_NUM = 24;

    std::vector<int> players_pos;
    int BONBI_playser_id;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[0], players_pos, BONBI_playser_id);

    const std::array<std::set<int>, 2> reachable_nodes = solver::solveBruteForce(Graph, players_pos, BONBI_playser_id, DICE_NUM, MAP_NUM);

    const std::array<std::set<int>, 2> reachable_nodes_handmade = {
        std::set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 22, 23},
        std::set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 18, 19, 20, 21, 22, 23, 23}
    };

    ASSERT_EQ(reachable_nodes, reachable_nodes_handmade);
}