#include <vector>
#include <fstream>
#include <cassert>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "CSVLoader.hpp"

namespace {
    std::vector<int> getSeparated(const std::string& buf) {
        std::vector<int> input_values;
        
        std::string elm;
        std::istringstream iss(buf);
        while(getline(iss, elm, ',')) {
            const size_t val = stoi(elm);
            input_values.emplace_back(val);
        }
        return input_values;
    }
}

const std::vector<std::vector<int>> loadGraphFromCSV(const std::string& file_path, std::vector<int>& users_status) {
    users_status.clear();

    std::vector<std::vector<int>> Graph;

    std::ifstream ifs_map_csv(file_path);
    std::cout << "Opening " << file_path << std::endl;
    assert(ifs_map_csv);

    std::string buf;
    size_t node_idx = 0;

    // First line
    assert(getline(ifs_map_csv, buf));
    assert(buf.find(',') == std::string::npos);
    const size_t node_num = stoi(buf);

    Graph.resize(node_num);
    std::cout << "Num of node is " << node_num << std::endl;

    // Following node_num lines
    for (size_t i=0; i<node_num; ++i) {
        getline(ifs_map_csv, buf);
        std::vector<int> input_values = getSeparated(buf);

        for (const size_t& val: input_values) {
            assert(node_idx < Graph.size());
            Graph[node_idx].emplace_back(val);
        }
        node_idx++;
    }

    // Last line
    assert(getline(ifs_map_csv, buf));
    std::vector<int> input_values = getSeparated(buf);
    if (input_values.size() > 4) {
        std::cerr << "Users status should be less than or equal to 4" << std::endl;
        exit(1);
    }

    for (const size_t& val: input_values) {
        if (val != 0 and val != 1) {
            std::cerr << "Users status value should be 0 or 1" << std::endl;
            exit(1);
        }
        users_status.emplace_back(val);
    }

    
    for (auto& vec: Graph) { std::sort(vec.begin(), vec.end()); }

    return Graph;
}