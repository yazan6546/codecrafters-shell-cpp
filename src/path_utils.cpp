#include "path_utils.h"
#include <filesystem>
#include <sstream>
#include <cstdlib>

namespace path_utils {
    std::string get_env(const std::string& key) {
        const char* value = std::getenv(key.c_str());
        return value ? std::string{value} : "";
    }

    std::string search_paths(const std::string& paths, const std::string& command) {
        std::stringstream stream(paths);
        std::string path_string;

        while (std::getline(stream, path_string, ':')) {
            std::filesystem::path path(path_string);
            if (std::filesystem::exists(path / command)) {
                return (path / command).string();
            }
        }
        return "";
    }
}