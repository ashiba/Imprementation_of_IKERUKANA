#ifndef IKERUKANA_DP_SOLVER_HPP_
#define IKERUKANA_DP_SOLVER_HPP_

#include <vector>
#include <cstddef>
#include <set>

namespace solver {
    const int NON_DIRECTION = 999;

    const std::vector<std::vector<char>> getDirectionTable(const std::vector<std::vector<int>>& Graph);

    struct BFS_Status {
        size_t remaining_move;
        size_t node_num;
        size_t direction = NON_DIRECTION;
    };

    const std::set<size_t> solveIkerukanaDP(const std::vector<std::vector<int>>& Graph, const size_t& DICE_NUM, const size_t& MAP_NUM);
}

#endif