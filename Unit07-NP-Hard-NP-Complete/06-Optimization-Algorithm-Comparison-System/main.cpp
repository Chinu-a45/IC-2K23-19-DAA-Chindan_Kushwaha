/**
 * Unit 7: NP-Hard, NP-Complete & Advanced Optimization
 * Experiment 6: APPLICATION - Optimization Algorithm Comparison System
 * 
 * Unified benchmarking suite comparing:
 * 1. Exhaustive Search (Brute Force O(2^n))
 * 2. Dynamic Programming (Pseudo-polynomial O(n*W))
 * 3. Branch and Bound (Pruned Search Tree)
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

struct Item { int id, w, v; double r; };

// Exhaustive
int solveExhaustive(int n, int W, const std::vector<Item>& items) {
    int max_p = 0;
    for (unsigned long long mask = 0; mask < (1ULL << n); ++mask) {
        int tw = 0, tv = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1ULL << i)) { tw += items[i].w; tv += items[i].v; }
        }
        if (tw <= W && tv > max_p) max_p = tv;
    }
    return max_p;
}

// DP
int solveDP(int n, int W, const std::vector<Item>& items) {
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (items[i - 1].w <= w)
                dp[i][w] = std::max(dp[i - 1][w], items[i - 1].v + dp[i - 1][w - items[i - 1].w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][W];
}

// Branch and Bound
struct Node {
    int lvl, prof, wt;
    double bound;
    bool operator<(const Node& o) const { return bound < o.bound; }
};

double calcBound(Node u, int n, int W, const std::vector<Item>& items) {
    if (u.wt >= W) return 0;
    double p = u.prof;
    int j = u.lvl + 1, tw = u.wt;
    while (j < n && tw + items[j].w <= W) {
        tw += items[j].w; p += items[j].v; j++;
    }
    if (j < n) p += (W - tw) * items[j].r;
    return p;
}

int solveBB(int n, int W, std::vector<Item> items) {
    std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) { return a.r > b.r; });
    std::priority_queue<Node> pq;
    Node u{-1, 0, 0, 0.0}, v;
    u.bound = calcBound(u, n, W, items);
    pq.push(u);
    int max_p = 0;
    while (!pq.empty()) {
        u = pq.top(); pq.pop();
        if (u.bound <= max_p) continue;
        v.lvl = u.lvl + 1;
        if (v.lvl >= n) continue;

        v.wt = u.wt + items[v.lvl].w;
        v.prof = u.prof + items[v.lvl].v;
        if (v.wt <= W && v.prof > max_p) max_p = v.prof;
        v.bound = calcBound(v, n, W, items);
        if (v.bound > max_p) pq.push(v);

        v.wt = u.wt; v.prof = u.prof;
        v.bound = calcBound(v, n, W, items);
        if (v.bound > max_p) pq.push(v);
    }
    return max_p;
}

int main() {
    std::cout << "===============================================================\n";
    std::cout << "  Unit 07 - Experiment 06: Optimization Comparison System     \n";
    std::cout << "===============================================================\n";

    std::vector<int> sizes = {8, 12, 16, 20};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,exhaustive_ms,dp_ms,bb_ms\n";

    std::cout << std::setw(6) << "n" 
              << std::setw(16) << "Exhaustive(ms)" 
              << std::setw(16) << "DP (ms)" 
              << std::setw(16) << "BB (ms)" << "\n";
    std::cout << std::string(54, '-') << "\n";

    for (int n : sizes) {
        int W = n * 10;
        std::vector<Item> items;
        for (int i = 0; i < n; ++i) {
            int w = 2 + (i * 3) % 15;
            int v = 10 + (i * 5) % 40;
            items.push_back({i + 1, w, v, static_cast<double>(v) / w});
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        int ex_res = solveExhaustive(n, W, items);
        auto t2 = std::chrono::high_resolution_clock::now();
        double ex_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        int dp_res = solveDP(n, W, items);
        auto t4 = std::chrono::high_resolution_clock::now();
        double dp_ms = std::chrono::duration<double, std::milli>(t4 - t3).count();

        auto t5 = std::chrono::high_resolution_clock::now();
        int bb_res = solveBB(n, W, items);
        auto t6 = std::chrono::high_resolution_clock::now();
        double bb_ms = std::chrono::duration<double, std::milli>(t6 - t5).count();

        csv << n << "," << std::scientific << std::setprecision(8) << (bb_ms * 1e-3) << ","
            << std::fixed << std::setprecision(3) << ex_ms << "," << dp_ms << "," << bb_ms << "\n";

        std::cout << std::setw(6) << n 
                  << std::setw(16) << std::fixed << std::setprecision(3) << ex_ms 
                  << std::setw(16) << dp_ms 
                  << std::setw(16) << bb_ms << "\n";
    }

    csv.close();
    std::cout << "\nOptimization Comparison System completed. Exported to results.csv.\n";
    return 0;
}
