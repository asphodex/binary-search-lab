//
// Created by sphdx on 06.04.2025.
//

#ifndef FILEREADER_H
#define FILEREADER_H
#include <fstream>
#include <string>

#include "Slog.h"

template<typename T, typename... Types>
concept ComplexType = requires(T t, std::string str, int counter)
{
    t.parse(str, counter);
};

class FileReader {
    FileReader() = default;
public:
    template<ComplexType T, typename... Types>
    static T* read_file(const std::string &file_path, size_t lines_to_read);
};

template<ComplexType T, typename... Types>
T* FileReader::read_file(const std::string &file_path, size_t lines_to_read) {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        Slog::error("couldn't open file", Slog::opt("file path", file_path));

        throw std::runtime_error("couldn't open file");
    }

    std::string line;
    int counter = 0;

    auto arr = new T[lines_to_read]{};

    while (std::getline(file, line) && counter < lines_to_read) {
        if (line.empty()) {
            counter++;
            continue;
        }

        auto el = new T;
        el->template parse<Types...>(line, counter);

        arr[counter] = *el;

        counter++;
    }
    return arr;
}

#endif //FILEREADER_H
