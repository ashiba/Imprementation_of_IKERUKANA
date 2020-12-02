#include <vector>
#include <fstream>
#include <cassert>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "CSVLoader.hpp"

const std::vector<std::vector<int>> loadGraphFromCSV(const std::string& file_path) {
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

    for (auto& vec: Graph) { std::sort(vec.begin(), vec.end()); }

    return Graph;
}