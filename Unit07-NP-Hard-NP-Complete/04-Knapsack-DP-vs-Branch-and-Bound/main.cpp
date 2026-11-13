/**
 * Unit 7: NP-Hard, NP-Complete & Advanced Optimization
 * Experiment 4: 0/1 Knapsack: Dynamic Programming vs Branch and Bound
 * 
 * Compares pseudo-polynomial O(n*W) table evaluation of DP against
 * branch pruning search of Branch and Bound across varying capacities W and item counts n.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

struct Item { int id, w, v; double r; };

// DP Solver
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

// Branch and Bound Solver
struct Node {
    int lvl, prof, wt;
    double bound;
    bool operator<(const Node& o) const { return bound < o.bound; }
};

double calcBound(Node u, int n, int W, const std::vector<Item>& items) {
    if (u.wt >= W) return 0;
    double p_bound = u.prof;
    int j = u.lvl + 1, tot_w = u.wt;
    while (j < n && tot_w + items[j].w <= W) {
        tot_w += items[j].w;
        p_bound += items[j].v;
        j++;
    }
    if (j < n) p_bound += (W - tot_w) * items[j].r;
    return p_bound;
}

std::pair<int, long long> solveBB(int n, int W, std::vector<Item> items) {
    std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) { return a.r > b.r; });
    std::priority_queue<Node> pq;
    Node u{-1, 0, 0, 0.0}, v;
    u.bound = calcBound(u, n, W, items);
    pq.push(u);
    int max_p = 0;
    long long nodes = 0;

    while (!pq.empty()) {
        u = pq.top(); pq.pop();
        nodes++;
        if (u.bound <= max_p) continue;
        v.lvl = u.lvl + 1;
        if (v.lvl >= n) continue;

        v.wt = u.wt + items[v.lvl].w;
        v.prof = u.prof + items[v.lvl].v;
        if (v.wt <= W && v.prof > max_p) max_p = v.prof;
        v.bound = calcBound(v, n, W, items);
        if (v.bound > max_p) pq.push(v);

        v.wt = u.wt;
        v.prof = u.prof;
        v.bound = calcBound(v, n, W, items);
        if (v.bound > max_p) pq.push(v);
    }
    return {max_p, nodes};
}

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 07 - Experiment 04: Knapsack DP vs Branch & Bound\n";
    std::cout << "========================================================\n";

    std::vector<int> sizes = {10, 15, 20, 25, 28};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,dp_ms,bb_ms,bb_nodes\n";

    std::cout << std::setw(6) << "n" 
              << std::setw(14) << "Capacity" 
              << std::setw(16) << "DP Time(ms)" 
              << std::setw(16) << "BB Time(ms)" 
              << std::setw(16) << "BB Nodes" << "\n";
    std::cout << std::string(68, '-') << "\n";

    for (int n : sizes) {
        int W = n * 50;
        std::vector<Item> items;
        for (int i = 0; i < n; ++i) {
            int w = 5 + (i * 7) % 30;
            int v = 20 + (i * 11) % 70;
            items.push_back({i + 1, w, v, static_cast<double>(v) / w});
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        int dp_ans = solveDP(n, W, items);
        auto t2 = std::chrono::high_resolution_clock::now();
        double dp_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        auto [bb_ans, bb_nodes] = solveBB(n, W, items);
        auto t4 = std::chrono::high_resolution_clock::now();
        double bb_ms = std::chrono::duration<double, std::milli>(t4 - t3).count();

        csv << n << "," << std::scientific << std::setprecision(8) << (bb_ms * 1e-3) << ","
            << std::fixed << std::setprecision(3) << dp_ms << "," << bb_ms << "," << bb_nodes << "\n";

        std::cout << std::setw(6) << n 
                  << std::setw(14) << W 
                  << std::setw(16) << std::fixed << std::setprecision(3) << dp_ms 
                  << std::setw(16) << bb_ms 
                  << std::setw(16) << bb_nodes << "\n";
    }

    csv.close();
    return 0;
}
