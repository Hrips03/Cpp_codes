#include <iostream>
#include "manager.hpp"
#include "merge_sort.hpp"

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7, 3, 10, 4, 1};

    std::cout << "Given array:\n";
    for (int num : arr) std::cout << num << " ";
    std::cout << "\n";

    Manager pool(std::thread::hardware_concurrency());
    parallelMergeSort(pool, arr, 0, arr.size() - 1);

    std::cout << "Sorted array:\n";
    for (int num : arr) std::cout << num << " ";
    std::cout << "\n";

    return 0;
}
