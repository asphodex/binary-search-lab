//
// Created by sphdx on 06.04.2025.
//

#ifndef LINEARSEARCH_H
#define LINEARSEARCH_H

#include <utility>

class LinearSearch {
    LinearSearch() = default;

public:
    LinearSearch(const LinearSearch &) = delete;

    LinearSearch &operator=(const LinearSearch &) = delete;

    template<typename T>
    static std::pair<int, int> linear_search(T *arr, int size, T target);
};

template<typename T>
std::pair<int, int> LinearSearch::linear_search(T *arr, int size, T target) {
    int last_found_index = -1, steps = 0;
    for (int i = 0; i < size; i++) {
        ++steps;

        // Slog::info("[LS] running", Slog::opt("step", steps), Slog::opt("size", size),
        //            Slog::opt("arr[i]", arr[i]));

        if (arr[i] == target) {
            last_found_index = i;
        }

        if (arr[i] > target) {
            break;
        }
    }

    return std::make_pair(last_found_index, steps);
}

#endif //LINEARSEARCH_H
