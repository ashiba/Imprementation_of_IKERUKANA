#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstring>
#include <set>

#include "NormalIkerukanaSolver.hpp"
#include "solver_util.hpp"


namespace solver {
    const std::set<size_t> solveBruteForce(const std::vector<std::vector<int>>& Graph, const size_t& DICE_NUM, const size_t& MAP_NUM) {
        if (DICE_NUM == 0) {
            return {0};
        } else if (DICE_NUM < 0) {
            std::cout << "DICE_NUM is less than 0 ??? ( " << DICE_NUM << " )" << std::endl;
            return {};
        }

        std::set<size_t> reachable_nodes;

        const std::vector<std::vector<char>> direction_table = getDirectionTable(Graph);

        std::queue<BFS_Status> que;
        que.push(BFS_Status{DICE_NUM, 0, NON_DIRECTION});
        while(not que.empty()) {
            const BFS_Status que_front = que.front();
            que.pop();
            assert(Graph[que_front.node_num].size() <= 4);
            
            if ((int)que_front.remaining_move <= 0 ) { // 探索終了
                assert((int)que_front.remaining_move == 0);
                reachable_nodes.insert(que_front.node_num);
            } else {
                for (const size_t& dist_node: Graph[que_front.node_num]) {  // 隣接するノードを探索
                    if ((size_t)direction_table[que_front.node_num][dist_node] == que_front.direction) continue; // 前回通ったノードへの移動はNG

                    que.push(BFS_Status{que_front.remaining_move-1, dist_node, (size_t)direction_table[dist_node][que_front.node_num]});
                }
            }
        }

        return reachable_nodes;
    }
}