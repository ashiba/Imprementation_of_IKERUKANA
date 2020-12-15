#ifndef IKERUKANA_DP_SOLVER_HPP_
#define IKERUKANA_DP_SOLVER_HPP_

#include <vector>
#include <cstddef>
#include <set>
#include <array>

namespace solver {
    const std::array<std::set<int>, 2> solveIkerukanaDP(const std::vector<std::vector<int>>& Graph, const std::vector<int>& players_pos, const int& BONBI_playler_id, const int& DICE_NUM, const int& MAP_NUM);
}

#endif