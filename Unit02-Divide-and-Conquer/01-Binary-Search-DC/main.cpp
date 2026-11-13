/**
 * Unit 2: Divide and Conquer
 * Experiment 1: Binary Search using Divide and Conquer
 * 
 * Recurrence: T(n) = T(n/2) + O(1) => T(n) = O(log n)
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>

class BinarySearchDC {
public:
    static int search(const std::vector<int>& arr, int low, int high, int target, int& subproblem_count) {
        subproblem_count++;
        if (low > high) return -1;

        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;

        // Divide step: choose left or right half
        if (target < arr[mid]) {
            return search(arr, low, mid - 1, target, subproblem_count);
        } else {
            return search(arr, mid + 1, high, target, subproblem_count);
        }
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "    Unit 02 - Experiment 01: Binary Search (D&C)    \n";
    std::cout << "====================================================\n";

    std::vector<int> sample = {3, 8, 15, 24, 33, 42, 59, 68, 77, 85, 96};
    int target = 42;
    int subproblems = 0;
    int idx = BinarySearchDC::search(sample, 0, sample.size() - 1, target, subproblems);
    std::cout << "Target: " << target << " found at index: " << idx 
              << " | Subproblems visited: " << subproblems << "\n";

    // Benchmark
    std::vector<int> sizes = {1000, 2000, 5000, 10000, 25000, 50000, 100000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,subproblems\n";

    std::cout << "\nBenchmark Results:\n";
    std::cout << std::setw(10) << "n" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ns)" 
              << std::setw(16) << "Subproblems" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (int n : sizes) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) arr[i] = i * 2;
        int q = arr[n * 2 / 3];

        const int RUNS = 200;
        auto start = std::chrono::high_resolution_clock::now();
        int sp = 0;
        for (int r = 0; r < RUNS; ++r) {
            sp = 0;
            BinarySearchDC::search(arr, 0, n - 1, q, sp);
        }
        auto end = std::chrono::high_resolution_clock::now();
        double avg_ns = std::chrono::duration<double, std::nano>(end - start).count() / RUNS;
        double avg_sec = avg_ns * 1e-9;

        csv << n << "," << std::scientific << std::setprecision(8) << avg_sec << "," << sp << "\n";

        std::cout << std::setw(10) << n 
                  << std::setw(18) << std::scientific << std::setprecision(4) << avg_sec
                  << std::setw(16) << std::fixed << std::setprecision(2) << avg_ns
                  << std::setw(16) << sp << "\n";
    }

    csv.close();
    return 0;
}
