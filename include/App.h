//
// Created by sphdx on 06.04.2025.
//

#ifndef APP_H
#define APP_H

#include <chrono>
#include <utility>

#include "BinarySearch.h"
#include "CmdInput.h"
#include "data-types/CollectedType.h"
#include "FileReader.h"
#include "generator.h"
#include "LinearSearch.h"
#include "ShellSort.h"
#include "slog.h"


// output :
// line
// steps of each alg

template<typename T>
concept TargetType = requires(T t, std::string str)
{
    t.parse(str);
};

class App {
    class SearchResult {
        int index_, steps_;
        std::chrono::milliseconds time_;

    public:
        SearchResult(const int &index, const int &steps, const std::chrono::milliseconds &time);

        [[nodiscard]] const int &get_index() const;

        [[nodiscard]] const int &get_steps() const;

        [[nodiscard]] std::chrono::milliseconds get_time() const;
    };

    template<typename T>
    T *convert(CollectedType *ct, int size);

    template<typename T>
    SearchResult perform_search_and_bench(std::pair<int, int> search(T *, int, T), T *arr, int size, T target);

    template<typename T>
    static void write_array_to_file(const std::string &output_file_path,
                                    const std::string &output_file_prefix, T *arr, int size);

    static void write_result_to_file(const std::string &output_file_path,
                                     const std::string &output_file_prefix,
                                     const SearchResult &binary_search_result,
                                     const SearchResult &linear_search_result);

public:
    App() = default;

    ~App() = default;

    template<TargetType T>
    void run(const std::string &input_file, const std::string &output_file_path,
             const std::string &output_file_prefix);
};

inline App::SearchResult::SearchResult(const int &index, const int &steps,
                                       const std::chrono::milliseconds &time) : index_(index), steps_(steps),
    time_(time) {
}


inline const int &App::SearchResult::get_index() const {
    return index_;
}

inline const int &App::SearchResult::get_steps() const {
    return steps_;
}

inline std::chrono::milliseconds App::SearchResult::get_time() const {
    return time_;
}

inline void App::write_result_to_file(const std::string &output_file_path, const std::string &output_file_prefix,
                                      const SearchResult &binary_search_result,
                                      const SearchResult &linear_search_result) {
    std::ofstream file(output_file_path + output_file_prefix);
    if (!file.is_open()) {
        throw std::runtime_error("couldn't open output file: " + output_file_path + output_file_prefix);
    }

    file << "Binary search:" << std::endl;
    file << "\t - index: " << binary_search_result.get_index() << std::endl;
    file << "\t - steps: " << binary_search_result.get_steps() << std::endl;
    file << "\t - time: " << binary_search_result.get_time() << std::endl;

    std::cout << std::endl;

    file << "Linear search:" << std::endl;
    file << "\t - index: " << linear_search_result.get_index() << std::endl;
    file << "\t - steps: " << linear_search_result.get_steps() << std::endl;
    file << "\t - time: " << linear_search_result.get_time() << std::endl;

    file.close();
}

template<typename T>
T *App::convert(CollectedType *ct, const int size) {
    T *result = new T[size];
    for (int i = 0; i < size; ++i) {
        if constexpr (std::is_same_v<T, LicensePlate>) {
            result[i] = ct[i].get_license_plate();
        } else if constexpr (std::is_same_v<T, PersonName>) {
            result[i] = ct[i].get_person_name();
        } else if constexpr (std::is_same_v<T, Car>) {
            result[i] = ct[i].get_car();
        } else if constexpr (std::is_same_v<T, Application>) {
            result[i] = ct[i].get_application();
        }
    }

    return result;
}

template<typename T>
App::SearchResult App::perform_search_and_bench(std::pair<int, int> search(T *arr, int size, T target), T *arr,
                                                const int size, T target) {
    const auto start = std::chrono::steady_clock::now();

    auto res = search(arr, size, target);

    const auto end = std::chrono::steady_clock::now();
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    return SearchResult{res.first, res.second, elapsed};
}

template<typename T>
void App::write_array_to_file(const std::string &output_file_path, const std::string &output_file_prefix, T *arr,
    const int size) {

    std::ofstream file(output_file_path + output_file_prefix);
    if (!file) {
        throw std::runtime_error("couldn't open file " + output_file_path + output_file_prefix);
    }

    for (size_t i = 0; i < size; ++i) {
        file << arr[i] << std::endl;
    }

    file.close();
}


template<TargetType T>
void App::run(const std::string &input_file, const std::string &output_file_path,
              const std::string &output_file_prefix) {
    std::cout << "Enter the count of lines to read from file: " << std::endl;

    const auto lines_to_read = CmdInput::get_number();

    std::cout << "Enter the target: " << std::endl;

    const auto raw_target = CmdInput::get_line();

    Slog::info("start reading file", Slog::opt("path", input_file));

    const auto ctypes = FileReader::read_file<CollectedType, LicensePlate, PersonName, Car, Application>(
        input_file, lines_to_read);

    auto arr = convert<T>(ctypes, lines_to_read);

    ShellSort::shell_sort(arr, lines_to_read);

    write_array_to_file(output_file_path, "sorted_input.txt", arr, lines_to_read);

    auto target = T::parse(raw_target);

    Slog::info("starting search", Slog::opt("target", target));

    auto binary_search_result = perform_search_and_bench<T>(BinarySearch::binary_search, arr, lines_to_read, target);
    Slog::info("binary search done", Slog::opt("index", binary_search_result.get_index()),
               Slog::opt("steps", binary_search_result.get_steps()),
               Slog::opt("time", binary_search_result.get_time()));

    auto linear_search_result = perform_search_and_bench<T>(LinearSearch::linear_search, arr, lines_to_read, target);
    Slog::info("linear search done", Slog::opt("index", linear_search_result.get_index()),
               Slog::opt("steps", linear_search_result.get_steps()),
               Slog::opt("time", linear_search_result.get_time()));

    write_result_to_file(output_file_path, output_file_prefix, binary_search_result, linear_search_result);

    Slog::info("wrote result", Slog::opt("path", output_file_path));
}
#endif //APP_H
