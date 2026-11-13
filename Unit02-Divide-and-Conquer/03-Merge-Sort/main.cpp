/**
 * Unit 2: Divide and Conquer
 * Experiment 3: Merge Sort
 * 
 * Recurrence: T(n) = 2T(n/2) + O(n) => T(n) = O(n log n) across all cases.
 * Auxiliary space: O(n)
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>
#include <algorithm>

class MergeSort {
private:
    static void merge(std::vector<int>& arr, int low, int mid, int high) {
        std::vector<int> temp(high - low + 1);
        int i = low, j = mid + 1, k = 0;

        while (i <= mid && j <= high) {
            if (arr[i] <= arr[j]) temp[k++] = arr[i++];
            else temp[k++] = arr[j++];
        }
        while (i <= mid) temp[k++] = arr[i++];
        while (j <= high) temp[k++] = arr[j++];

        for (int p = 0; p < k; ++p) {
            arr[low + p] = temp[p];
        }
    }

public:
    static void sort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int mid = low + (high - low) / 2;
            sort(arr, low, mid);
            sort(arr, mid + 1, high);
            merge(arr, low, mid, high);
        }
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "        Unit 02 - Experiment 03: Merge Sort         \n";
    std::cout << "====================================================\n";

    std::vector<int> sample = {64, 34, 25, 12, 22, 11, 90, 88, 76, 45};
    std::cout << "Original: ";
    for (int x : sample) std::cout << x << " ";
    std::cout << "\n";

    MergeSort::sort(sample, 0, sample.size() - 1);

    std::cout << "Sorted:   ";
    for (int x : sample) std::cout << x << " ";
    std::cout << "\nVerified sorted: " << (std::is_sorted(sample.begin(), sample.end()) ? "YES" : "NO") << "\n";

    // Benchmark across various sizes
    std::vector<int> sizes = {1000, 2000, 5000, 10000, 25000, 50000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,time_ms\n";

    std::cout << "\nBenchmark Table:\n";
    std::cout << std::setw(10) << "n" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ms)" << "\n";
    std::cout << std::string(44, '-') << "\n";

    std::mt19937 rng(1337);
    for (int n : sizes) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) arr[i] = rng() % 1000000;

        auto start = std::chrono::high_resolution_clock::now();
        MergeSort::sort(arr, 0, n - 1);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
        double elapsed_sec = elapsed_ms * 1e-3;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << std::fixed << std::setprecision(4) << elapsed_ms << "\n";

        std::cout << std::setw(10) << n 
                  << std::setw(18) << std::scientific << std::setprecision(4) << elapsed_sec
                  << std::setw(16) << std::fixed << std::setprecision(4) << elapsed_ms << "\n";
    }

    csv.close();
    return 0;
}
