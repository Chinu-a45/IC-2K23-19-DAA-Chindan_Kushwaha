/**
 * Unit 2: Divide and Conquer
 * Experiment 5: Heap Sort
 * 
 * Time Complexity: O(n log n) in all cases (Build Heap: O(n), n-1 sift-downs: O(n log n))
 * Space Complexity: O(1) auxiliary (in-place)
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>
#include <algorithm>

class HeapSort {
public:
    static void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) largest = left;
        if (right < n && arr[right] > arr[largest]) largest = right;

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    static void sort(std::vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        // 1. Build Max Heap in O(n)
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(arr, n, i);
        }
        // 2. Extract max element and sift down
        for (int i = n - 1; i > 0; --i) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "         Unit 02 - Experiment 05: Heap Sort         \n";
    std::cout << "====================================================\n";

    std::vector<int> sample = {12, 11, 13, 5, 6, 7, 33, 2, 89, 45};
    HeapSort::sort(sample);
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

    std::mt19937 rng(999);
    for (int n : sizes) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) arr[i] = rng() % 1000000;

        auto start = std::chrono::high_resolution_clock::now();
        HeapSort::sort(arr);
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
