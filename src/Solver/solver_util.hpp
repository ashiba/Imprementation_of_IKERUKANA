#ifndef SOLVER_UTIL_HPP_
#define SOLVER_UTIL_HPP_

#include <cstddef>
#include <vector>
#include <cassert>
#include <algorithm>

namespace solver{
    const size_t DIRECTION_NUM = 4;
    const int MAX_PLAYERS_NUM = 4;
    const int NON_DIRECTION = 999;

    struct BFS_Status {
        int remaining_move;
        int node_num;
        int direction = NON_DIRECTION;
    };

    struct BFS_Status_with_bonbi {
        int remaining_move;
        int node_num;
        int direction = NON_DIRECTION;
        int player_with_BONBI_id;
    };

    
    inline const std::vector<std::vector<char>> getDirectionTable(const std::vector<std::vector<int>>& Graph) {
        std::vector<std::vector<char>> direction_table(Graph.size(), std::vector<char>(Graph.size(), 99));
        for (size_t i=0; i<Graph.size(); ++i) {
            assert(Graph[i].size() <=4 );
            for (size_t j=0; j<Graph[i].size(); ++j) {
                direction_table[i][Graph[i][j]] = j;
            }
        }
        return direction_table;
    }

    inline bool isVectorIncludesTheID(const std::vector<int>& the_player_ids, const int& BONBI_playler_id) {
        return (std::find(the_player_ids.begin(), the_player_ids.end(), BONBI_playler_id) != the_player_ids.end());
    }

    inline std::vector<int> whichPlayersOn(const int& dist_node, const std::vector<int>& players_pos) {
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
#endif