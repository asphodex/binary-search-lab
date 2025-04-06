//
// Created by sphdx on 06.04.2025.
//

#ifndef SHELLSORT_H
#define SHELLSORT_H

class ShellSort {
    // increment generates Sedjvick dist for shell sort
    static inline int increment(long long inc[], long size);
    ShellSort() = default;
public:
    ShellSort(const ShellSort &) = delete;

    ShellSort &operator=(const ShellSort &) = delete;


    enum class Order {
        ASC,
        DESC
    };

    template<typename T>
    static void shell_sort(T *arr, int arraySize, Order order = Order::ASC);
};

inline int ShellSort::increment(long long inc[], const long size) {
    int p1 = 1, p2 = 1, p3 = 1;
    int s = -1;

    do {
        if (++s % 2) {
            inc[s] = 8 * p1 - 6 * p2 + 1;
        } else {
            inc[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
    } while (3 * inc[s] < size);

    return s > 0 ? --s : 0;
}

template<typename T>
void ShellSort::shell_sort(T *arr, const int arraySize, const Order order) {
    long j;
    long long seq[30];

    int s = increment(seq, arraySize);

    while (s >= 0) {
        const long inc = seq[s--];

        for (long i = inc; i < arraySize; i++) {
            T temp = arr[i];

            if (order == Order::ASC) {
                for (j = i - inc; j >= 0 && arr[j] > temp; j -= inc) {
                    arr[j + inc] = arr[j];
                }
            } else {
                for (j = i - inc; j >= 0 && arr[j] < temp; j -= inc) {
                    arr[j + inc] = arr[j];
                }
            }

            arr[j + inc] = temp;
        }
    }
}

#endif //SHELLSORT_H
