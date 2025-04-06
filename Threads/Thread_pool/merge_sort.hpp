#pragma once
#include <vector>
#include "manager.hpp"

void parallelMergeSort(Manager& pool, std::vector<int>& arr, int left, int right);
void merge(std::vector<int>& arr, int left, int mid, int right);