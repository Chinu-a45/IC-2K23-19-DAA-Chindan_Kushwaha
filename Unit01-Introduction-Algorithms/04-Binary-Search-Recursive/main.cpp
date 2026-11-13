/**
 * Unit 1: Introduction to Algorithms & Performance Analysis
 * Experiment 4: Recursive Binary Search
 * 
 * Problem: Implement recursive binary search using divide-and-conquer recurrence.
 * Recurrence: T(n) = T(n/2) + O(1) => O(log n)
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>

class BinarySearchRecursive {
public:
    static int searchRecursive(const std::vector<int>& arr, int low, int high, int target, int& call_depth) {
        call_depth++;
        if (low > high) return -1;

        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;

        if (arr[mid] > target) {
            return searchRecursive(arr, low, mid - 1, target, call_depth);
        } else {
            return searchRecursive(arr, mid + 1, high, target, call_depth);
        }
    }

    static std::pair<int, double> benchmark(const std::vector<int>& arr, int target, int& depth) {
        depth = 0;
        auto start = std::chrono::high_resolution_clock::now();
        int idx = searchRecursive(arr, 0, static_cast<int>(arr.size()) - 1, target, depth);
        auto end = std::chrono::high_resolution_clock::now();
        double elapsed_ns = std::chrono::duration<double, std::nano>(end - start).count();
        return {idx, elapsed_ns};
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "  Unit 01 - Experiment 04: Recursive Binary Search  \n";
    std::cout << "====================================================\n";

    // 1. Correctness validation
    std::vector<int> sample = {10, 22, 35, 47, 51, 63, 75, 88, 92, 105};
    int target = 63;
    int depth = 0;
    auto res = BinarySearchRecursive::benchmark(sample, target, depth);
    std::cout << "Target: " << target << " -> Index: " << res.first 
              << " | Recursion Depth: " << depth 
              << " | Time: " << res.second << " ns\n";

    // 2. Benchmark across multiple sizes
    std::vector<int> sizes = {1000, 2000, 5000, 10000, 20000, 50000, 100000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,depth\n";

    std::cout << "\nEmpirical Performance Benchmark:\n";
    std::cout << std::setw(10) << "n" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ns)" 
              << std::setw(16) << "Depth (log2 n)" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (int n : sizes) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) arr[i] = i * 3;

        int query = arr[n / 3];
        const int RUNS = 200;
        double total_ns = 0;
        int d = 0;
        for (int r = 0; r < RUNS; ++r) {
            auto b = BinarySearchRecursive::benchmark(arr, query, d);
            total_ns += b.second;
        }
        double avg_ns = total_ns / RUNS;
        double avg_sec = avg_ns * 1e-9;

        csv << n << "," << std::scientific << std::setprecision(8) << avg_sec << "," << d << "\n";

        std::cout << std::setw(10) << n 
                  << std::setw(18) << std::scientific << std::setprecision(4) << avg_sec
                  << std::setw(16) << std::fixed << std::setprecision(2) << avg_ns
                  << std::setw(16) << d << "\n";
    }

    csv.close();
    std::cout << "\nResults recorded to results.csv successfully.\n";
    return 0;
}
