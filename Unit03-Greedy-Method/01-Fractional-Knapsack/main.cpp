/**
 * Unit 3: Greedy Method
 * Experiment 1: Fractional Knapsack
 * 
 * Strategy: Sort items descending by profit-to-weight ratio (p_i / w_i).
 * Take whole items while capacity allows, then take a fraction of the next item.
 * Time Complexity: O(n log n) sorting + O(n) greedy scan = O(n log n).
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

struct Item {
    int id;
    double weight;
    double value;
    double ratio;

    Item(int id, double weight, double value)
        : id(id), weight(weight), value(value), ratio(value / weight) {}
};

class FractionalKnapsack {
public:
    static double solve(std::vector<Item>& items, double capacity, std::vector<std::pair<int, double>>& chosen) {
        std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.ratio > b.ratio;
        });

        double total_value = 0.0;
        double remaining_capacity = capacity;

        for (const auto& item : items) {
            if (remaining_capacity <= 0.0) break;

            if (item.weight <= remaining_capacity) {
                total_value += item.value;
                remaining_capacity -= item.weight;
                chosen.push_back({item.id, 1.0});
            } else {
                double fraction = remaining_capacity / item.weight;
                total_value += item.value * fraction;
                chosen.push_back({item.id, fraction});
                remaining_capacity = 0.0;
                break;
            }
        }
        return total_value;
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "    Unit 03 - Experiment 01: Fractional Knapsack    \n";
    std::cout << "====================================================\n";

    std::vector<Item> items = {
        Item(1, 10, 60),
        Item(2, 20, 100),
        Item(3, 30, 120)
    };
    double capacity = 50.0;

    std::vector<std::pair<int, double>> chosen;
    double max_profit = FractionalKnapsack::solve(items, capacity, chosen);

    std::cout << "Knapsack Capacity: " << capacity << "\n";
    std::cout << "Selected Item Allocations:\n";
    for (auto& p : chosen) {
        std::cout << "  Item " << p.first << ": " << std::fixed << std::setprecision(2) << (p.second * 100.0) << "% taken\n";
    }
    std::cout << "Maximum Achievable Profit: " << max_profit << " (Expected: 240.0)\n";

    // Benchmark across different numbers of items
    std::vector<int> sizes = {1000, 5000, 10000, 25000, 50000, 100000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,max_profit\n";

    std::cout << "\nBenchmark Table:\n";
    std::cout << std::setw(10) << "n" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ms)" 
              << std::setw(18) << "Total Profit" << "\n";
    std::cout << std::string(62, '-') << "\n";

    for (int n : sizes) {
        std::vector<Item> test_items;
        test_items.reserve(n);
        for (int i = 0; i < n; ++i) {
            double w = 1.0 + (i % 50);
            double v = 10.0 + (i % 100);
            test_items.emplace_back(i + 1, w, v);
        }
        double cap = n * 15.0;

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::pair<int, double>> ch;
        double prof = FractionalKnapsack::solve(test_items, cap, ch);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
        double elapsed_sec = elapsed_ms * 1e-3;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << std::fixed << std::setprecision(2) << prof << "\n";

        std::cout << std::setw(10) << n 
                  << std::setw(18) << std::scientific << std::setprecision(4) << elapsed_sec
                  << std::setw(16) << std::fixed << std::setprecision(4) << elapsed_ms
                  << std::setw(18) << prof << "\n";
    }

    csv.close();
    return 0;
}
