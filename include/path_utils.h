#pragma once
#include <string>

namespace path_utils {
    std::string get_env(const std::string& key);
    std::string search_paths(const std::string& paths, const std::string& command);
}