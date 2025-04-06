//
// Created by sphdx on 03.03.2025.
//

#ifndef PATH_H
#define PATH_H

#include <string>
#include <filesystem>

static std::string get_absolute_file_path(const std::string &relative_path) {
    const std::filesystem::path current_path = std::filesystem::current_path();
    const std::filesystem::path absolute_file_path = current_path / "../" / relative_path;

    return absolute_file_path.string();
}

#endif //PATH_H
