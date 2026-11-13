/**
 * Unit 7: NP-Hard, NP-Complete & Advanced Optimization
 * Experiment 1: Exhaustive Search Demonstration
 * 
 * Demonstrates exponential combinatorial explosion on 0/1 Knapsack (2^n states)
 * and factorial explosion on TSP ((n-1)! permutations).
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

class ExhaustiveKnapsack {
public:
    static std::pair<int, unsigned long long> solve(const std::vector<int>& weights, 
                                                    const std::vector<int>& values, int W) {
        int n = weights.size();
        int max_val = 0;
        unsigned long long evaluated = 0;

        for (unsigned long long mask = 0; mask < (1ULL << n); ++mask) {
            evaluated++;
            int cur_w = 0;
            int cur_v = 0;
            for (int i = 0; i < n; ++i) {
                if (mask & (1ULL << i)) {
                    cur_w += weights[i];
                    cur_v += values[i];
                }
            }
            if (cur_w <= W && cur_v > max_val) {
                max_val = cur_v;
            }
        }
        return {max_val, evaluated};
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 07 - Experiment 01: Exhaustive Search Explosion  \n";
    std::cout << "========================================================\n";

    std::vector<int> weights = {2, 3, 4, 5, 9};
    std::vector<int> values = {3, 4, 5, 8, 10};
    int W = 10;

    auto [best_val, states] = ExhaustiveKnapsack::solve(weights, values, W);
    std::cout << "Sample Knapsack (n=5, W=10):\n";
    std::cout << "  Maximum Profit: " << best_val << "\n";
    std::cout << "  Total Configurations Evaluated (2^n): " << states << "\n";

    // Benchmark across n = 10 to 24
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,states_evaluated,time_ms\n";

    std::cout << "\nBenchmark Table (Exponential Search Space Growth):\n";
    std::cout << std::setw(6) << "n" 
              << std::setw(18) << "States (2^n)" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ms)" << "\n";
    std::cout << std::string(58, '-') << "\n";

    for (int n = 10; n <= 22; n += 2) {
        std::vector<int> wt(n), val(n);
        for (int i = 0; i < n; ++i) {
            wt[i] = 1 + (i % 7);
            val[i] = 5 + (i % 13);
        }
        int cap = n * 3;

        auto start = std::chrono::high_resolution_clock::now();
        auto r = ExhaustiveKnapsack::solve(wt, val, cap);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
        double elapsed_sec = elapsed_ms * 1e-3;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << r.second << "," << std::fixed << std::setprecision(4) << elapsed_ms << "\n";

        std::cout << std::setw(6) << n 
                  << std::setw(18) << r.second 
                  << std::setw(18) << std::scientific << std::setprecision(4) << elapsed_sec
                  << std::setw(16) << std::fixed << std::setprecision(4) << elapsed_ms << "\n";
    }

    csv.close();
    return 0;
}
