#ifndef CSV_LOADER_HPP_
#define CSV_LOADER_HPP_

#include <vector>
#include <string>

const std::vector<std::vector<int>> loadGraphFromCSV(const std::string& file_path, std::vector<int>& users_status);

#endif