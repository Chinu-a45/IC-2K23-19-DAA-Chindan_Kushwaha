/**
 * Unit 7: NP-Hard, NP-Complete & Advanced Optimization
 * Experiment 2: 0/1 Knapsack using Branch and Bound
 * 
 * Uses LC-Search (Least Cost Search) with max-priority queue ordered by upper bound.
 * Upper Bound calculated via Fractional Knapsack relaxation.
 */

#include <iostream>
#include <vector>
#include <queue>
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

struct Node {
    int level;
    int profit;
    int weight;
    double bound;

    bool operator<(const Node& other) const {
        return bound < other.bound; // Max-heap based on upper bound
    }
};

class KnapsackBranchBound {
public:
    static double calculateBound(Node u, int n, int W, const std::vector<Item>& items) {
        if (u.weight >= W) return 0;
        double profit_bound = u.profit;
        int j = u.level + 1;
        int totweight = u.weight;

        while (j < n && totweight + items[j].weight <= W) {
            totweight += items[j].weight;
            profit_bound += items[j].value;
            j++;
        }

        if (j < n) {
            profit_bound += (W - totweight) * items[j].ratio;
        }
        return profit_bound;
    }

    static std::pair<int, long long> solve(std::vector<Item> items, int W) {
        std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.ratio > b.ratio;
        });

        int n = items.size();
        std::priority_queue<Node> pq;

        Node u{-1, 0, 0, 0.0};
        Node v;

        u.bound = calculateBound(u, n, W, items);
        pq.push(u);

        int max_profit = 0;
        long long nodes_visited = 0;

        while (!pq.empty()) {
            u = pq.top();
            pq.pop();
            nodes_visited++;

            if (u.bound <= max_profit) continue;

            v.level = u.level + 1;
            if (v.level >= n) continue;

            // Branch 1: Include item v.level
            v.weight = u.weight + items[v.level].weight;
            v.profit = u.profit + items[v.level].value;

            if (v.weight <= W && v.profit > max_profit) {
                max_profit = v.profit;
            }
            v.bound = calculateBound(v, n, W, items);
            if (v.bound > max_profit) pq.push(v);

            // Branch 2: Exclude item v.level
            v.weight = u.weight;
            v.profit = u.profit;
            v.bound = calculateBound(v, n, W, items);
            if (v.bound > max_profit) pq.push(v);
        }

        return {max_profit, nodes_visited};
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 07 - Experiment 02: Knapsack Branch & Bound      \n";
    std::cout << "========================================================\n";

    std::vector<Item> items = {
        {1, 2, 40, 20.0},
        {2, 3, 50, 16.67},
        {3, 4, 100, 25.0},
        {4, 5, 95, 19.0},
        {5, 7, 30, 4.3}
    };
    int W = 10;

    auto [profit, nodes] = KnapsackBranchBound::solve(items, W);
    std::cout << "Optimal Profit: " << profit << "\n";
    std::cout << "Nodes Visited: " << nodes << "\n";

    // Benchmark across various instance sizes
    std::vector<int> sizes = {10, 15, 20, 25, 30};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,nodes_explored,max_profit\n";

    for (int n : sizes) {
        std::vector<Item> test_items;
        for (int i = 0; i < n; ++i) {
            int w = 2 + (i * 3) % 15;
            int v = 10 + (i * 7) % 50;
            test_items.push_back({i + 1, w, v, static_cast<double>(v) / w});
        }
        int cap = n * 5;

        auto start = std::chrono::high_resolution_clock::now();
        auto res = KnapsackBranchBound::solve(test_items, cap);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_sec = std::chrono::duration<double>(end - start).count();
        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << res.second << "," << res.first << "\n";
    }

    csv.close();
    std::cout << "Benchmark exported to results.csv.\n";
    return 0;
}
