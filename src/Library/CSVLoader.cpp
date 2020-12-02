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

const std::vector<std::vector<int>> loadGraphFromCSV(const std::string& file_path, std::vector<int>& players_pos, int& BONBI_player_num) {
    players_pos.clear();

    std::vector<std::vector<int>> Graph;

    std::ifstream ifs_map_csv(file_path);
    std::cout << "Opening " << file_path << std::endl;
    if (not ifs_map_csv) {
        std::cout << file_path << " can't be opened." << std::endl;
        exit(1);
    }

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
        assert(getline(ifs_map_csv, buf));
        std::vector<int> input_values = getSeparated(buf);

        for (const size_t& val: input_values) {
            assert(node_idx < Graph.size());
            Graph[node_idx].emplace_back(val);
        }
        node_idx++;
    }

    // load player num
    assert(getline(ifs_map_csv, buf)); std::cout << "players_num" << buf << std::endl;
    assert(buf.find(',') == std::string::npos);
    const size_t player_num = stoi(buf);

    // load players_pos
    assert(getline(ifs_map_csv, buf));
    std::vector<int> input_values = getSeparated(buf);
    if (input_values.size() > player_num) {
        std::cerr << "players positions sequence should be less than or equal to player_num" << std::endl;
        exit(1);
    }
    for (const size_t& val: input_values) {
        if (val < 0 or val >= node_num) {
            std::cerr << "Invalid players positions value" << std::endl;
            exit(1);
        }
        players_pos.emplace_back(val);
    }

    // load BONBI data
    assert(getline(ifs_map_csv, buf));
    assert(buf.find(',') == std::string::npos);
    BONBI_player_num = stoi(buf);

    
    for (auto& vec: Graph) { std::sort(vec.begin(), vec.end()); }

    return Graph;
}