/**
 * Unit 2: Divide and Conquer
 * Experiment 2: Maximum and Minimum using Divide and Conquer
 * 
 * Recurrence: T(n) = 2T(n/2) + 2 comparisons => T(n) = 3n/2 - 2 comparisons
 * Standard sequential search requires 2n - 2 comparisons.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>

struct MinMax {
    int min_val;
    int max_val;
    int comparisons;
};

class DivideConquerMinMax {
public:
    static MinMax findMinMax(const std::vector<int>& arr, int low, int high) {
        MinMax result{0, 0, 0};

        // Base Case 1: Single element
        if (low == high) {
            result.min_val = arr[low];
            result.max_val = arr[low];
            result.comparisons = 0;
            return result;
        }

        // Base Case 2: Two elements
        if (high == low + 1) {
            result.comparisons = 1;
            if (arr[low] > arr[high]) {
                result.min_val = arr[high];
                result.max_val = arr[low];
            } else {
                result.min_val = arr[low];
                result.max_val = arr[high];
            }
            return result;
        }

        // Divide & Conquer Step
        int mid = low + (high - low) / 2;
        MinMax left = findMinMax(arr, low, mid);
        MinMax right = findMinMax(arr, mid + 1, high);

        // Combine: 2 comparisons
        result.min_val = (left.min_val < right.min_val) ? left.min_val : right.min_val;
        result.max_val = (left.max_val > right.max_val) ? left.max_val : right.max_val;
        result.comparisons = left.comparisons + right.comparisons + 2;

        return result;
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "      Unit 02 - Experiment 02: Max-Min (D&C)        \n";
    std::cout << "====================================================\n";

    std::vector<int> sample = {28, 9, 45, 12, 73, 3, 91, 54, 38, 17};
    MinMax res = DivideConquerMinMax::findMinMax(sample, 0, sample.size() - 1);
    std::cout << "Array size: " << sample.size() << "\n";
    std::cout << "Minimum: " << res.min_val << " | Maximum: " << res.max_val 
              << " | Comparisons: " << res.comparisons 
              << " (Theoretical 3n/2 - 2: " << (3 * sample.size() / 2 - 2) << ")\n";

    // Benchmark
    std::vector<int> sizes = {1000, 5000, 10000, 25000, 50000, 100000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,comparisons,theoretical_comparisons\n";

    std::cout << "\nBenchmark Table:\n";
    std::cout << std::setw(10) << "n" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (us)" 
              << std::setw(16) << "Empirical Comps" 
              << std::setw(16) << "Theory Comps" << "\n";
    std::cout << std::string(76, '-') << "\n";

    std::mt19937 rng(42);
    for (int n : sizes) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) arr[i] = rng() % 1000000;

        auto start = std::chrono::high_resolution_clock::now();
        MinMax out = DivideConquerMinMax::findMinMax(arr, 0, n - 1);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
        double elapsed_sec = elapsed_us * 1e-6;
        int theory = 3 * n / 2 - 2;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << out.comparisons << "," << theory << "\n";

        std::cout << std::setw(10) << n 
                  << std::setw(18) << std::scientific << std::setprecision(4) << elapsed_sec
                  << std::setw(16) << std::fixed << std::setprecision(2) << elapsed_us
                  << std::setw(16) << out.comparisons
                  << std::setw(16) << theory << "\n";
    }

    csv.close();
    return 0;
}
