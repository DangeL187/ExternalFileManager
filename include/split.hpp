#ifndef EXTERNALFILEMANAGER_SPLIT_HPP
#define EXTERNALFILEMANAGER_SPLIT_HPP

#include <ranges>
#include <string_view>
#include <vector>

std::vector<std::string> split(const std::string& string, const std::string& delim);

#endif //EXTERNALFILEMANAGER_SPLIT_HPP
