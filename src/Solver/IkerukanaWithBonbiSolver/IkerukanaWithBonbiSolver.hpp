#ifndef IKERUKANA_SOLVER_HPP_
#define IKERUKANA_SOLVER_HPP_

#include <array>
#include <vector>
#include <cstddef>
#include <set>

namespace solver {
    const std::array<std::set<int>, 2> solveBruteForce(const std::vector<std::vector<int>>& Graph, const std::vector<int>& players_pos, const int& BONBI_playler_id, const int& DICE_NUM, const int& MAP_NUM);
}

#endif