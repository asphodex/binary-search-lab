//
// Created by sphdx on 06.04.2025.
//

#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <functional>
#include <utility>

#include "Slog.h"

class BinarySearch {
    BinarySearch() = default;

public:
    BinarySearch(const BinarySearch &) = delete;

    BinarySearch &operator=(const BinarySearch &) = delete;

    template<typename T>
    static std::pair<int, int> binary_search(T *arr, int size, T target);
};

template<typename T>
std::pair<int, int> BinarySearch::binary_search(T *arr, const int size, T target) {
    int steps = 0;

    std::function<int(int, int)> search = [&](const int left, const int right) -> int {
        if (left > right)
            return -1;

        steps++;

        int mid = left + (right - left) / 2;
        // Slog::info("[BS] running", Slog::opt("step", steps), Slog::opt("left", left),
        //            Slog::opt("right", right),
        //            Slog::opt("arr[mid]", arr[mid]));

        if (arr[mid] == target) {
            const int index_right = search(mid + 1, right);
            return index_right != -1 ? index_right : mid;
        }

        if (arr[mid] < target) {
            return search(mid + 1, right);
        }

        return search(left, mid - 1);
    };

    const int index = search(0, size - 1);
    return std::make_pair(index, steps);
}


#endif //BINARY_SEARCH_H
