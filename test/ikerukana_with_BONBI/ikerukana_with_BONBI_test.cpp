#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cassert>
#include <queue>
#include <algorithm>
#include <set>
#include <array>

#include "ikerukanaDPSolver.hpp"
#include "CSVLoader.hpp"
#include "gtest/gtest.h"

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

std::vector<std::string> maps_path = {"ktbdmr_map_with_2players.csv"};

namespace {
    bool isVectorIncludesTheID(const std::vector<int>& the_player_ids, const int& BONBI_playler_id) {
        return (std::find(the_player_ids.begin(), the_player_ids.end(), BONBI_playler_id) != the_player_ids.end());
    }

    std::vector<int> whichPlayersOn(const int& dist_node, const std::vector<int>& players_pos) {
        std::vector<int> players;
        // 自分は除くためiの初期値は1
        for (size_t i=1; i<players_pos.size(); ++i) {
            if (players_pos[i] == dist_node) {
                players.emplace_back(i);
            }
        }
        return players;
    }
}

namespace solver {
    const std::array<std::set<int>, 2> solveBruteForce(const std::vector<std::vector<int>>& Graph, const std::vector<int>& players_pos, const int& BONBI_playler_id, const int& DICE_NUM, const int& MAP_NUM) {
        if (BONBI_playler_id < 0 or BONBI_playler_id >= (int)players_pos.size()) {
            std::cout << "Invalid BONBI_player_id. " << BONBI_playler_id << std::endl;
            return {};
        }
        if (DICE_NUM == 0) {
            return {std::set<int>{players_pos[0]}, std::set<int>{players_pos[0]}};
        } else if (DICE_NUM < 0) {
            std::cout << "DICE_NUM is less than 0 ??? ( " << DICE_NUM << " )" << std::endl;
            return {};
        }

        const int MY_PLAYER_ID = 0;
        const int NON_DIRECTION = 999;
        const int NO_BONBI = 0;
        const int WITH_BONBI = 1;
        std::array<std::set<int>, 2> reachable_nodes;



        const std::vector<std::vector<char>> direction_table = getDirectionTable(Graph);

        struct BFS_Status {
            int remaining_move;
            int node_num;
            int direction = NON_DIRECTION;
            int player_with_BONBI_id;
        };

        std::queue<BFS_Status> que;
        que.push(BFS_Status{DICE_NUM, players_pos[0], NON_DIRECTION, BONBI_playler_id});
        while(not que.empty()) {
            const BFS_Status que_front = que.front();
            que.pop();
            assert(Graph[que_front.node_num].size() <= 4);
            for (const int& dist_node: Graph[que_front.node_num]) {
                if (direction_table[que_front.node_num][dist_node] == que_front.direction) continue;

                int new_player_with_BONBI_id;
                if ((int)que_front.remaining_move-1 > 0) {
                    const std::vector<int> the_player_ids = whichPlayersOn(dist_node, players_pos);
                    const bool does_anyone_on_dist_node_has_BONBIE = isVectorIncludesTheID(the_player_ids, que_front.player_with_BONBI_id);

                    if (the_player_ids.empty() or (not does_anyone_on_dist_node_has_BONBIE and MY_PLAYER_ID != que_front.player_with_BONBI_id)) {
                    // 無人のマスへの移動 or 自分もそのマスのプレイヤーもボンビーを持たない場合の移動
                        new_player_with_BONBI_id = que_front.player_with_BONBI_id;

                    } else if (does_anyone_on_dist_node_has_BONBIE) { // 移動先のマスにボンビーを持っているプレイヤーがいる
                        new_player_with_BONBI_id = MY_PLAYER_ID;

                    } else if (MY_PLAYER_ID == que_front.player_with_BONBI_id and not the_player_ids.empty()) { // 自分がボンビーを持っていて移動先に他のプレイヤーがいる
                        new_player_with_BONBI_id = the_player_ids[0];

                    } else { // 空集合
                        std::cout << "Something is wrog if you reached here." << std::endl;
                        exit(1);
                    }
                    que.push(BFS_Status{que_front.remaining_move-1, dist_node, direction_table[dist_node][que_front.node_num], new_player_with_BONBI_id});
                } else {
                    assert((int)que_front.remaining_move-1 == 0);
                    if (que_front.player_with_BONBI_id == MY_PLAYER_ID) {
                        reachable_nodes[WITH_BONBI].insert(dist_node);
                    } else {
                        reachable_nodes[WITH_BONBI].insert(dist_node);
                        reachable_nodes[NO_BONBI  ].insert(dist_node);
                    }
                }
            }
        }

        return reachable_nodes;
    }
}


TEST(loadGraphFromCSVTest, checkLoadedGraphData) {
    std::vector<int> players_pos;
    int BONBI_playser_id;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[0], players_pos, BONBI_playser_id);

    ASSERT_EQ(Graph.size(), 24);

    std::vector<std::vector<int>>Graph_handmade = {
        {1, 3},
        {0, 2, 23},
        {1, 3},
        {0, 2, 4, 5},
        {3, 8},
        {3, 6},
        {5, 7, 8},
        {6},
        {4, 6, 9},
        {8, 10},
        {9, 11, 22},
        {10, 12},
        {11, 13},
        {12, 14},
        {13, 15},
        {14, 16, 17},
        {15, 18},
        {15, 18},
        {16, 17, 19},
        {18, 20},
        {19, 21},
        {20, 22},
        {10, 21},
        {1},
    };

    const std::vector<int> players_pos_handmade = {0, 3};

    ASSERT_EQ(Graph, Graph_handmade);
    EXPECT_EQ(players_pos.size(), 2);
    EXPECT_EQ(players_pos, players_pos_handmade);
    EXPECT_EQ(BONBI_playser_id, 1);

}

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