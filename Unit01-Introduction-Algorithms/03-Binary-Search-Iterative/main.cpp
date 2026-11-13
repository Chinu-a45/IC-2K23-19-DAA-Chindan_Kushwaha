/**
 * Unit 1: Introduction to Algorithms & Performance Analysis
 * Experiment 3: Iterative Binary Search
 * 
 * Problem: Implement iterative binary search with loop invariant verification,
 * comparison counting, and high-resolution empirical performance measurement.
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <algorithm>

struct SearchResult {
    int index;
    int comparisons;
    double time_ns;
};

class BinarySearchIterative {
public:
    static SearchResult search(const std::vector<int>& arr, int target) {
        auto start = std::chrono::high_resolution_clock::now();
        int low = 0;
        int high = static_cast<int>(arr.size()) - 1;
        int comparisons = 0;

        while (low <= high) {
            comparisons++;
            int mid = low + (high - low) / 2;
            if (arr[mid] == target) {
                auto end = std::chrono::high_resolution_clock::now();
                double elapsed = std::chrono::duration<double, std::nano>(end - start).count();
                return {mid, comparisons, elapsed};
            }
            if (arr[mid] < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        double elapsed = std::chrono::duration<double, std::nano>(end - start).count();
        return {-1, comparisons, elapsed};
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "  Unit 01 - Experiment 03: Iterative Binary Search  \n";
    std::cout << "====================================================\n";

    // 1. Correctness Verification
    std::vector<int> sample = {5, 12, 18, 23, 39, 45, 56, 67, 78, 89, 99};
    int target = 45;
    SearchResult res = BinarySearchIterative::search(sample, target);
    std::cout << "Sample Array Size: " << sample.size() << "\n";
    std::cout << "Target: " << target << " -> Found at index: " << res.index 
              << " | Comparisons: " << res.comparisons 
              << " | Time: " << res.time_ns << " ns\n";

    // 2. Benchmark for different input sizes n
    std::vector<int> test_sizes = {1000, 2000, 5000, 10000, 20000, 50000, 100000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,comparisons\n";

    std::cout << "\nEmpirical Performance Benchmark:\n";
    std::cout << std::setw(10) << "n" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ns)" 
              << std::setw(16) << "Comparisons" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (int n : test_sizes) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) arr[i] = i * 2; // Even numbers sorted

        // Query element at 75% position (average case)
        int query = arr[n * 3 / 4];

        // Warm up and average 100 runs
        double total_time_ns = 0;
        int comps = 0;
        const int RUNS = 200;
        for (int r = 0; r < RUNS; ++r) {
            auto r_res = BinarySearchIterative::search(arr, query);
            total_time_ns += r_res.time_ns;
            comps = r_res.comparisons;
        }
        double avg_ns = total_time_ns / RUNS;
        double avg_sec = avg_ns * 1e-9;

        csv << n << "," << std::scientific << std::setprecision(8) << avg_sec << "," << comps << "\n";

        std::cout << std::setw(10) << n 
                  << std::setw(18) << std::scientific << std::setprecision(4) << avg_sec
                  << std::setw(16) << std::fixed << std::setprecision(2) << avg_ns
                  << std::setw(16) << comps << "\n";
    }

    csv.close();
    std::cout << "\nResults recorded to results.csv successfully.\n";
    return 0;
}
