#ifndef CSV_LOADER_HPP_
#define CSV_LOADER_HPP_

#include <vector>
#include <string>

const std::vector<std::vector<int>> loadGraphFromCSV(const std::string& file_path, std::vector<int>& players_status, int& player_num);

#endif