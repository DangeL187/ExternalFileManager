#include "split.hpp"

std::vector<std::string> split(const std::string& string, const std::string& delim) {
    auto split = string | std::ranges::views::split(delim)
                 | std::ranges::views::transform([](auto&& str) {
                     return std::string_view(&*str.begin(), std::ranges::distance(str));
                 });

    std::vector<std::string> output;
    for (auto&& word: split) {
        output.push_back(static_cast<const std::basic_string<char>>(word));
    }
    return output;
}