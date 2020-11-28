#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cassert>

#include "gtest/gtest.h"

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

std::vector<std::string> maps_path = {"ktbdmr_map.csv"};


std::vector<std::vector<int>> loadGraphFromCSV(const std::string& file_path) {
    std::vector<std::vector<int>> Graph;

    std::ifstream ifs_map_csv(file_path);
    std::cout << "Opening " << file_path << std::endl;
    assert(ifs_map_csv);

    std::string buf;
    size_t node_idx = 0;

    // First line
    assert(getline(ifs_map_csv, buf));
    assert(buf.find(',') == std::string::npos);
    const size_t val = stoi(buf);

    Graph.resize(val);
    std::cout << "Num of node is " << val << std::endl;

    // Othre line
    while (getline(ifs_map_csv, buf)) {
        std::vector<int> input_values;
        {
            std::string elm;
            std::istringstream iss(buf);
            while(getline(iss, elm, ',')) {
                const size_t val = stoi(elm);
                input_values.emplace_back(val);
            }
        }

        for (const size_t& val: input_values) {
            assert(node_idx < Graph.size());
            Graph[node_idx].emplace_back(val);
        }
        node_idx++;
    }
    return Graph;
}

TEST(loadGraphFromCSVTest, checkLoadedGraphData) {
    std::vector<std::vector<int>> Graph = loadGraphFromCSV(STRINGIFY(MAPS_DIR)"/" + maps_path[0]);

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
