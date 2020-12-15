#ifndef IKERUKANA_SOLVER_HPP_
#define IKERUKANA_SOLVER_HPP_

#include <vector>
#include <cstddef>
#include <set>

namespace solver {
    const std::set<size_t> solveBruteForce(const std::vector<std::vector<int>>& Graph, const size_t& DICE_NUM, const size_t& MAP_NUM);
}

#endif