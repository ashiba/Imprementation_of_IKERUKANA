#include <vector>

#include "CSVLoader.hpp"
#include "gtest/gtest.h"

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

std::vector<std::string> maps_path = {"ktbdmr_map.csv", "ktbdmr_map_with_2players.csv"};

TEST(loadGraphFromCSVTest, checkLoadedGraphData1) {
    std::vector<int> users_pos;
    int BONBI_data;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[0], users_pos, BONBI_data);

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

    ASSERT_EQ(Graph, Graph_handmade);

}


TEST(loadGraphFromCSVTest, checkLoadedGraphData2) {
    std::vector<int> players_pos;
    int BONBI_playser_id;
    const std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[1], players_pos, BONBI_playser_id);

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