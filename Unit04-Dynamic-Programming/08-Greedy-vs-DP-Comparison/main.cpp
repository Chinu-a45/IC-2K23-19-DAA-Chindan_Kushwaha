/**
 * Unit 4: Dynamic Programming
 * Experiment 8: Greedy vs Dynamic Programming Comparison
 * 
 * Demonstrates scenarios where Greedy fails to find global optimum (e.g. 0/1 Knapsack)
 * while Dynamic Programming guarantees the exact global optimum.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

struct Item {
    int id;
    int weight;
    int value;
    double ratio;
};

class ComparisonStudy {
public:
    static int solveGreedy01(std::vector<Item> items, int W) {
        std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.ratio > b.ratio;
        });
        int cur_w = 0;
        int total_val = 0;
        for (const auto& it : items) {
            if (cur_w + it.weight <= W) {
                cur_w += it.weight;
                total_val += it.value;
            }
        }
        return total_val;
    }

    static int solveDP01(const std::vector<Item>& items, int W) {
        int n = items.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));
        for (int i = 1; i <= n; ++i) {
            for (int w = 0; w <= W; ++w) {
                if (items[i - 1].weight <= w) {
                    dp[i][w] = std::max(dp[i - 1][w], 
                                        items[i - 1].value + dp[i - 1][w - items[i - 1].weight]);
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        return dp[n][W];
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 04 - Experiment 08: Greedy vs Dynamic Programming \n";
    std::cout << "========================================================\n";

    // Classic counter-example for Greedy:
    // Capacity = 50
    // Item 1: wt=10, val=60 (ratio 6.0)
    // Item 2: wt=20, val=100 (ratio 5.0)
    // Item 3: wt=30, val=120 (ratio 4.0)
    // Greedy takes Item 1 & Item 2 => wt=30, profit=160.
    // DP takes Item 2 & Item 3 => wt=50, profit=220 (Optimal!).
    std::vector<Item> items = {
        {1, 10, 60, 6.0},
        {2, 20, 100, 5.0},
        {3, 30, 120, 4.0}
    };
    int capacity = 50;

    int greedy_res = ComparisonStudy::solveGreedy01(items, capacity);
    int dp_res = ComparisonStudy::solveDP01(items, capacity);

    std::cout << "Counter-example Instance (W = " << capacity << "):\n";
    std::cout << "  Greedy Heuristic Profit: " << greedy_res << " (Suboptimal!)\n";
    std::cout << "  Dynamic Programming:     " << dp_res << " (Global Optimum!)\n";
    std::cout << "  Greedy Suboptimality Gap: " << (dp_res - greedy_res) << " profit points ("
              << std::fixed << std::setprecision(1) << ((dp_res - greedy_res) * 100.0 / dp_res) << "% loss)\n";

    // Benchmark across various sizes
    std::vector<int> sizes = {50, 100, 200, 500, 1000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,greedy_val,dp_val,greedy_time_ms,dp_time_ms\n";

    std::cout << "\nBenchmark Table (Quality & Runtime):\n";
    std::cout << std::setw(8) << "n" 
              << std::setw(14) << "Greedy Val" 
              << std::setw(14) << "DP Val" 
              << std::setw(16) << "Greedy (ms)" 
              << std::setw(16) << "DP (ms)" << "\n";
    std::cout << std::string(68, '-') << "\n";

    for (int n : sizes) {
        int W = n * 10;
        std::vector<Item> test_items;
        for (int i = 0; i < n; ++i) {
            int w = 1 + (i % 25);
            int v = 10 + (i % 50);
            test_items.push_back({i + 1, w, v, static_cast<double>(v) / w});
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        int g_val = ComparisonStudy::solveGreedy01(test_items, W);
        auto t2 = std::chrono::high_resolution_clock::now();
        double g_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        int d_val = ComparisonStudy::solveDP01(test_items, W);
        auto t4 = std::chrono::high_resolution_clock::now();
        double d_ms = std::chrono::duration<double, std::milli>(t4 - t3).count();

        csv << n << "," << std::scientific << std::setprecision(8) << (d_ms * 1e-3) << ","
            << g_val << "," << d_val << "," << g_ms << "," << d_ms << "\n";

        std::cout << std::setw(8) << n 
                  << std::setw(14) << g_val 
                  << std::setw(14) << d_val 
                  << std::setw(16) << std::fixed << std::setprecision(4) << g_ms 
                  << std::setw(16) << d_ms << "\n";
    }

    csv.close();
    return 0;
}
