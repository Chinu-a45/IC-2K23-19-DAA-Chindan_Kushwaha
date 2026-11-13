/**
 * Unit 2: Divide and Conquer
 * Experiment 7: APPLICATION - Sorting Performance Comparison System
 * 
 * Problem: Comprehensive comparison of Merge Sort, Quick Sort, and Heap Sort
 * on Random, Already Sorted, and Reverse-Sorted inputs across different values of n.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>
#include <algorithm>

// Merge Sort
void merge(std::vector<int>& a, int l, int m, int h) {
    std::vector<int> t(h - l + 1);
    int i = l, j = m + 1, k = 0;
    while (i <= m && j <= h) t[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    while (i <= m) t[k++] = a[i++];
    while (j <= h) t[k++] = a[j++];
    for (int p = 0; p < k; ++p) a[l + p] = t[p];
}
void mergeSort(std::vector<int>& a, int l, int h) {
    if (l < h) {
        int m = l + (h - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, h);
        merge(a, l, m, h);
    }
}

// Quick Sort
int partition(std::vector<int>& a, int l, int h) {
    int mid = l + (h - l) / 2;
    std::swap(a[mid], a[h]);
    int p = a[h], i = l - 1;
    for (int j = l; j < h; ++j) {
        if (a[j] <= p) std::swap(a[++i], a[j]);
    }
    std::swap(a[i + 1], a[h]);
    return i + 1;
}
void quickSort(std::vector<int>& a, int l, int h) {
    if (l < h) {
        int pi = partition(a, l, h);
        quickSort(a, l, pi - 1);
        quickSort(a, pi + 1, h);
    }
}

// Heap Sort
void heapify(std::vector<int>& a, int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;
    if (largest != i) {
        std::swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}
void heapSort(std::vector<int>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapify(a, n, i);
    for (int i = n - 1; i > 0; --i) {
        std::swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

int main() {
    std::cout << "===============================================================\n";
    std::cout << "  Unit 02 - Experiment 07: Sorting Performance Comparison System\n";
    std::cout << "===============================================================\n";

    std::vector<int> sizes = {1000, 5000, 10000, 20000, 50000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,merge_ms,quick_ms,heap_ms\n";

    std::cout << std::setw(10) << "n"
              << std::setw(18) << "Merge Sort (ms)"
              << std::setw(18) << "Quick Sort (ms)"
              << std::setw(18) << "Heap Sort (ms)" << "\n";
    std::cout << std::string(64, '-') << "\n";

    std::mt19937 rng(42);
    for (int n : sizes) {
        std::vector<int> base(n);
        for (int i = 0; i < n; ++i) base[i] = rng() % 1000000;

        auto a1 = base;
        auto t1 = std::chrono::high_resolution_clock::now();
        mergeSort(a1, 0, n - 1);
        auto t2 = std::chrono::high_resolution_clock::now();
        double m_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();

        auto a2 = base;
        auto t3 = std::chrono::high_resolution_clock::now();
        quickSort(a2, 0, n - 1);
        auto t4 = std::chrono::high_resolution_clock::now();
        double q_ms = std::chrono::duration<double, std::milli>(t4 - t3).count();

        auto a3 = base;
        auto t5 = std::chrono::high_resolution_clock::now();
        heapSort(a3);
        auto t6 = std::chrono::high_resolution_clock::now();
        double h_ms = std::chrono::duration<double, std::milli>(t6 - t5).count();

        csv << n << "," << std::scientific << std::setprecision(8) << (q_ms * 1e-3) << ","
            << std::fixed << std::setprecision(4) << m_ms << "," << q_ms << "," << h_ms << "\n";

        std::cout << std::setw(10) << n
                  << std::setw(18) << std::fixed << std::setprecision(4) << m_ms
                  << std::setw(18) << q_ms
                  << std::setw(18) << h_ms << "\n";
    }

    csv.close();
    std::cout << "\nSorting comparison completed and exported to results.csv.\n";
    return 0;
}
