#include <vector>
#include <queue>
#include <iostream>
#include <cassert>
#include <cstring>
#include <set>

#include "IkerukanaWithBonbiSolver.hpp"
#include "solver_util.hpp"

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
        const int NO_BONBI = 0;
        const int WITH_BONBI = 1;
        std::array<std::set<int>, 2> reachable_nodes;


        const std::vector<std::vector<char>> direction_table = getDirectionTable(Graph);

        std::queue<BFS_Status_with_bonbi> que;
        que.push(BFS_Status_with_bonbi{DICE_NUM, players_pos[0], NON_DIRECTION, BONBI_playler_id});
        while(not que.empty()) {
            const BFS_Status_with_bonbi que_front = que.front();
            que.pop();
            assert(Graph[que_front.node_num].size() <= 4);
            
            if ((int)que_front.remaining_move <= 0) {
                assert((int)que_front.remaining_move == 0);
                if (que_front.player_with_BONBI_id == MY_PLAYER_ID) {
                    reachable_nodes[WITH_BONBI].insert(que_front.node_num);
                } else {
                    reachable_nodes[WITH_BONBI].insert(que_front.node_num);
                    reachable_nodes[NO_BONBI  ].insert(que_front.node_num);
                }
            } else {
                for (const int& dist_node: Graph[que_front.node_num]) {
                    if (direction_table[que_front.node_num][dist_node] == que_front.direction) continue;

                    int new_player_with_BONBI_id;
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
                        std::cout << "Something is wrong if you reached here." << std::endl;
                        exit(1);
                    }
                    que.push(BFS_Status_with_bonbi{que_front.remaining_move-1, dist_node, direction_table[dist_node][que_front.node_num], new_player_with_BONBI_id});
                }
            }
        }

        return reachable_nodes;
    }
}