#include "merge_sort.hpp"

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void parallelMergeSort(Manager& pool, std::vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    if (right - left > 1000) { // threshold to avoid too many threads
        std::atomic<int> counter(2);

        pool.submit([&pool, &arr, left, mid, &counter]() {
            parallelMergeSort(pool, arr, left, mid);
            --counter;
        });

        pool.submit([&pool, &arr, mid, right, &counter]() {
            parallelMergeSort(pool, arr, mid + 1, right);
            --counter;
        });

        // Wait for both to finish
        while (counter > 0) std::this_thread::yield();
    } else {
        parallelMergeSort(pool, arr, left, mid);
        parallelMergeSort(pool, arr, mid + 1, right);
    }

    merge(arr, left, mid, right);
}
