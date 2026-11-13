/**
 * Unit 4: Dynamic Programming
 * Experiment 2: Fibonacci using Memoization and Tabulation
 * 
 * Top-down Memoization: O(n) time, O(n) space.
 * Bottom-up Space-Optimized Tabulation: O(n) time, O(1) space.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

class DPFibonacci {
public:
    // Top-down with memoization
    static long long memoFib(int n, std::vector<long long>& memo) {
        if (n <= 0) return 0;
        if (n == 1) return 1;
        if (memo[n] != -1) return memo[n];
        return memo[n] = memoFib(n - 1, memo) + memoFib(n - 2, memo);
    }

    // Bottom-up Tabulation (Space-optimized O(1))
    static long long bottomUpFib(int n) {
        if (n <= 0) return 0;
        if (n == 1) return 1;
        long long prev2 = 0, prev1 = 1;
        for (int i = 2; i <= n; ++i) {
            long long curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 04 - Experiment 02: Fibonacci with Memoization   \n";
    std::cout << "========================================================\n";

    int n_sample = 40;
    std::vector<long long> memo(n_sample + 1, -1);
    long long ans_memo = DPFibonacci::memoFib(n_sample, memo);
    long long ans_tab = DPFibonacci::bottomUpFib(n_sample);

    std::cout << "F(" << n_sample << ") via Memoization: " << ans_memo << "\n";
    std::cout << "F(" << n_sample << ") via Tabulation:  " << ans_tab << "\n";

    // Benchmark up to large values of n (e.g. 100,000)
    std::vector<int> sizes = {1000, 5000, 10000, 25000, 50000, 100000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,time_us\n";

    std::cout << "\nBenchmark Table:\n";
    std::cout << std::setw(10) << "n" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (us)" << "\n";
    std::cout << std::string(44, '-') << "\n";

    for (int n : sizes) {
        auto start = std::chrono::high_resolution_clock::now();
        long long res = DPFibonacci::bottomUpFib(n % 90); // mod 90 to prevent 64-bit overflow for large n
        (void)res;
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
        double elapsed_sec = elapsed_us * 1e-6;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << std::fixed << std::setprecision(3) << elapsed_us << "\n";

        std::cout << std::setw(10) << n 
                  << std::setw(18) << std::scientific << std::setprecision(4) << elapsed_sec
                  << std::setw(16) << std::fixed << std::setprecision(3) << elapsed_us << "\n";
    }

    csv.close();
    return 0;
}
