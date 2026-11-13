/**
 * Unit 2: Divide and Conquer
 * Experiment 4: Quick Sort
 * 
 * Recurrence: Best/Average T(n) = 2T(n/2) + O(n) => O(n log n)
 * Worst Case: T(n) = T(n-1) + O(n) => O(n^2)
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>
#include <algorithm>

class QuickSort {
private:
    static int partition(std::vector<int>& arr, int low, int high) {
        // Median-of-three pivot to avoid worst-case on already sorted inputs
        int mid = low + (high - low) / 2;
        if (arr[mid] < arr[low]) std::swap(arr[low], arr[mid]);
        if (arr[high] < arr[low]) std::swap(arr[low], arr[high]);
        if (arr[high] < arr[mid]) std::swap(arr[mid], arr[high]);
        std::swap(arr[mid], arr[high]);

        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

public:
    static void sort(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            sort(arr, low, pi - 1);
            sort(arr, pi + 1, high);
        }
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "        Unit 02 - Experiment 04: Quick Sort         \n";
    std::cout << "====================================================\n";

    std::vector<int> sample = {54, 26, 93, 17, 77, 31, 44, 55, 20};
    QuickSort::sort(sample, 0, sample.size() - 1);
    std::cout << "Sorted Output: ";
    for (int x : sample) std::cout << x << " ";
    std::cout << "\nVerified sorted: " << (std::is_sorted(sample.begin(), sample.end()) ? "YES" : "NO") << "\n";

    // Benchmark
    std::vector<int> sizes = {1000, 2000, 5000, 10000, 25000, 50000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,time_ms\n";

    std::cout << "\nBenchmark Table:\n";
    std::cout << std::setw(10) << "n" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ms)" << "\n";
    std::cout << std::string(44, '-') << "\n";

    std::mt19937 rng(42);
    for (int n : sizes) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) arr[i] = rng() % 1000000;

        auto start = std::chrono::high_resolution_clock::now();
        QuickSort::sort(arr, 0, n - 1);
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
