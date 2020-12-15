#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cassert>
#include <queue>
#include <algorithm>
#include <set>

#include "NormalIkerukanaDPSolver.hpp"
#include "CSVLoader.hpp"
#include "gtest/gtest.h"

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

std::vector<std::string> maps_path = {"ktbdmr_map.csv"};


namespace solver {
    const std::set<size_t> solveBruteForce(const std::vector<std::vector<int>>& Graph, const size_t& DICE_NUM, const size_t& MAP_NUM) {
        if (DICE_NUM == 0) {
            return {0};
        } else if (DICE_NUM < 0) {
            std::cout << "DICE_NUM is less than 0 ??? ( " << DICE_NUM << " )" << std::endl;
            return {};
        }

        const int NON_DIRECTION = 999;
        std::set<size_t> reachable_nodes;

        const std::vector<std::vector<char>> direction_table = getDirectionTable(Graph);

        struct BFS_Status {
            size_t remaining_move;
            size_t node_num;
            size_t direction = NON_DIRECTION;
        };

        std::queue<BFS_Status> que;
        que.push(BFS_Status{DICE_NUM, 0, NON_DIRECTION});
        while(not que.empty()) {
            const BFS_Status que_front = que.front();
            que.pop();
            assert(Graph[que_front.node_num].size() <= 4);
            
            if ((int)que_front.remaining_move <= 0 ) {
                assert((int)que_front.remaining_move == 0);
                reachable_nodes.insert(que_front.node_num);
            } else {
                for (const size_t& dist_node: Graph[que_front.node_num]) {
                    if ((size_t)direction_table[que_front.node_num][dist_node] == que_front.direction) continue;

                    que.push(BFS_Status{que_front.remaining_move-1, dist_node, (size_t)direction_table[dist_node][que_front.node_num]});
                }
            }
        }

        return reachable_nodes;
    }
}


TEST(BFS_SolverTest, zeroDice) {
    const size_t DICE_NUM = 0;
    const size_t MAP_NUM = 24;

    std::vector<int> users_pos;
    int BONBI_data;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[0], users_pos, BONBI_data);
    ASSERT_EQ(Graph.size(), MAP_NUM);

    const std::set<size_t> reachable_node = solver::solveBruteForce(Graph, DICE_NUM, MAP_NUM);

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

    const std::set<size_t> reachable_node = solver::solveBruteForce(Graph, DICE_NUM, MAP_NUM);

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

    const std::set<size_t> reachable_node1 = solver::solveIkerukanaDP(Graph, DICE_NUM, MAP_NUM);

    const std::set<size_t> reachable_node2 = solver::solveBruteForce(Graph, DICE_NUM, MAP_NUM);

    ASSERT_EQ(reachable_node1, reachable_node2);
}
