/**
 * Unit 1: Introduction to Algorithms & Performance Analysis
 * Experiment 6: Execution Time Measurement and Empirical Graphs
 * 
 * Problem: Measure CPU and wall-clock execution time for different input sizes,
 * store experimental results in a file, and validate computational complexity.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>
#include <algorithm>

void performWorkload(int n) {
    // Standard O(n) operation with arithmetic accumulation
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) vec[i] = i ^ (i >> 2);
    long long sum = 0;
    for (int x : vec) sum += x;
    volatile long long dummy = sum;
    (void)dummy;
}

int main() {
    std::cout << "====================================================\n";
    std::cout << "  Unit 01 - Experiment 06: Execution Time Profiler  \n";
    std::cout << "====================================================\n";

    std::vector<int> input_sizes = {1000, 5000, 10000, 20000, 50000, 100000, 200000, 500000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,time_ms\n";

    std::cout << std::setw(12) << "n" 
              << std::setw(20) << "Time (seconds)" 
              << std::setw(16) << "Time (ms)" << "\n";
    std::cout << std::string(48, '-') << "\n";

    for (int n : input_sizes) {
        const int ITER = 20;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < ITER; ++i) {
            performWorkload(n);
        }
        auto end = std::chrono::high_resolution_clock::now();
        double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count() / ITER;
        double elapsed_sec = elapsed_ms * 1e-3;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec 
            << "," << std::fixed << std::setprecision(4) << elapsed_ms << "\n";

        std::cout << std::setw(12) << n 
                  << std::setw(20) << std::scientific << std::setprecision(4) << elapsed_sec 
                  << std::setw(16) << std::fixed << std::setprecision(4) << elapsed_ms << "\n";
    }

    csv.close();
    std::cout << "\nPerformance log saved to results.csv.\n";
    return 0;
}
