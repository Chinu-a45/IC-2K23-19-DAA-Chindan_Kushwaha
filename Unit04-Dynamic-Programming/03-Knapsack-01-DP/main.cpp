/**
 * Unit 4: Dynamic Programming
 * Experiment 3: 0/1 Knapsack using Dynamic Programming
 * 
 * Recurrence:
 * DP[i][w] = DP[i-1][w]                           if wt[i-1] > w
 * DP[i][w] = max(DP[i-1][w], val[i-1] + DP[i-1][w - wt[i-1]]) otherwise
 * Time Complexity: O(n * W), Space Complexity: O(n * W) with item reconstruction.
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
};

class KnapsackDP {
public:
    static std::pair<int, std::vector<int>> solve(const std::vector<Item>& items, int W) {
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

        // Backtrack to find selected items
        std::vector<int> selected;
        int cur_w = W;
        for (int i = n; i > 0 && cur_w > 0; --i) {
            if (dp[i][cur_w] != dp[i - 1][cur_w]) {
                selected.push_back(items[i - 1].id);
                cur_w -= items[i - 1].weight;
            }
        }
        return {dp[n][W], selected};
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "      Unit 04 - Experiment 03: 0/1 Knapsack DP      \n";
    std::cout << "====================================================\n";

    std::vector<Item> sample_items = {
        {1, 2, 12},
        {2, 1, 10},
        {3, 3, 20},
        {4, 2, 15}
    };
    int capacity = 5;

    auto result = KnapsackDP::solve(sample_items, capacity);
    std::cout << "Max Profit: " << result.first << " (Expected: 37)\n";
    std::cout << "Selected Items: ";
    for (int id : result.second) std::cout << "Item " << id << " ";
    std::cout << "\n";

    // Benchmark across various problem sizes (n * W)
    std::vector<std::pair<int, int>> configs = {
        {100, 100},
        {200, 200},
        {400, 400},
        {600, 600},
        {1000, 1000}
    };

    std::ofstream csv("results.csv");
    csv << "n,W,time_seconds,time_ms,max_profit\n";

    std::cout << "\nBenchmark Table:\n";
    std::cout << std::setw(8) << "Items(n)" 
              << std::setw(14) << "Capacity(W)" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ms)" 
              << std::setw(16) << "Max Profit" << "\n";
    std::cout << std::string(72, '-') << "\n";

    for (auto& cfg : configs) {
        int n = cfg.first;
        int W = cfg.second;

        std::vector<Item> test_items;
        for (int i = 0; i < n; ++i) {
            test_items.push_back({i + 1, 1 + (i % 20), 5 + (i % 50)});
        }

        auto start = std::chrono::high_resolution_clock::now();
        auto r = KnapsackDP::solve(test_items, W);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
        double elapsed_sec = elapsed_ms * 1e-3;

        csv << n << "," << W << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << std::fixed << std::setprecision(4) << elapsed_ms << "," << r.first << "\n";

        std::cout << std::setw(8) << n 
                  << std::setw(14) << W 
                  << std::setw(18) << std::scientific << std::setprecision(4) << elapsed_sec
                  << std::setw(16) << std::fixed << std::setprecision(4) << elapsed_ms
                  << std::setw(16) << r.first << "\n";
    }

    csv.close();
    return 0;
}
