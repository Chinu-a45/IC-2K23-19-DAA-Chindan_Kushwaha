/**
 * Unit 7: NP-Hard, NP-Complete & Advanced Optimization
 * Experiment 5: TSP: Dynamic Programming vs Branch and Bound
 * 
 * Direct performance benchmark comparing Held-Karp O(n^2 2^n) DP against
 * matrix-reduction Branch and Bound.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

constexpr int INF = 1e8;

// DP (Held-Karp)
int solveHeldKarp(int n, const std::vector<std::vector<int>>& dist) {
    int total_masks = 1 << n;
    std::vector<std::vector<int>> dp(total_masks, std::vector<int>(n, INF));
    dp[1][0] = 0;

    for (int mask = 1; mask < total_masks; ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u)) || dp[mask][u] == INF) continue;
            for (int v = 0; v < n; ++v) {
                if (!(mask & (1 << v))) {
                    dp[mask | (1 << v)][v] = std::min(dp[mask | (1 << v)][v], dp[mask][u] + dist[u][v]);
                }
            }
        }
    }
    int ans = INF;
    for (int u = 1; u < n; ++u) ans = std::min(ans, dp[(1 << n) - 1][u] + dist[u][0]);
    return ans;
}

// Branch and Bound
int reduce(int n, std::vector<std::vector<int>>& mat) {
    int cost = 0;
    for (int i = 0; i < n; ++i) {
        int m = INF;
        for (int j = 0; j < n; ++j) m = std::min(m, mat[i][j]);
        if (m != INF && m > 0) {
            cost += m;
            for (int j = 0; j < n; ++j) if (mat[i][j] != INF) mat[i][j] -= m;
        }
    }
    for (int j = 0; j < n; ++j) {
        int m = INF;
        for (int i = 0; i < n; ++i) m = std::min(m, mat[i][j]);
        if (m != INF && m > 0) {
            cost += m;
            for (int i = 0; i < n; ++i) if (mat[i][j] != INF) mat[i][j] -= m;
        }
    }
    return cost;
}

struct Node {
    std::vector<std::vector<int>> mat;
    int lvl, v, cost;
    bool operator>(const Node& o) const { return cost > o.cost; }
};

std::pair<int, long long> solveBB(int n, std::vector<std::vector<int>> cost) {
    std::priority_queue<Node, std::vector<Node>, std::greater<>> pq;
    Node root{cost, 0, 0, reduce(n, cost)};
    pq.push(root);
    int min_tour = INF;
    long long nodes = 0;

    while (!pq.empty()) {
        Node cur = pq.top(); pq.pop();
        nodes++;
        if (cur.cost >= min_tour) continue;
        if (cur.lvl == n - 1) {
            int ret = cost[cur.v][0];
            if (ret != INF && cur.cost + ret < min_tour) min_tour = cur.cost + ret;
            continue;
        }
        for (int v = 0; v < n; ++v) {
            if (cur.mat[cur.v][v] != INF) {
                Node ch{cur.mat, cur.lvl + 1, v, 0};
                for (int j = 0; j < n; ++j) ch.mat[cur.v][j] = INF;
                for (int i = 0; i < n; ++i) ch.mat[i][v] = INF;
                ch.mat[v][0] = INF;
                ch.cost = cur.cost + cur.mat[cur.v][v] + reduce(n, ch.mat);
                if (ch.cost < min_tour) pq.push(ch);
            }
        }
    }
    return {min_tour, nodes};
}

int main() {
    std::cout << "========================================================\n";
    std::cout << "   Unit 07 - Experiment 05: TSP DP vs Branch & Bound    \n";
    std::cout << "========================================================\n";

    std::vector<int> sizes = {4, 6, 8, 10, 12, 14};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,dp_ms,bb_ms,bb_nodes\n";

    std::cout << std::setw(6) << "n" 
              << std::setw(16) << "DP Time(ms)" 
              << std::setw(16) << "BB Time(ms)" 
              << std::setw(16) << "BB Nodes" << "\n";
    std::cout << std::string(54, '-') << "\n";

    for (int n : sizes) {
        std::vector<std::vector<int>> d(n, std::vector<int>(n, INF));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (i != j) d[i][j] = (i * 7 + j * 13) % 40 + 5;

        auto t1 = std::chrono::high_resolution_clock::now();
        int dp_res = solveHeldKarp(n, d);
        auto t2 = std::chrono::high_resolution_clock::now();
        double dp_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        auto [bb_res, bb_nodes] = solveBB(n, d);
        auto t4 = std::chrono::high_resolution_clock::now();
        double bb_ms = std::chrono::duration<double, std::milli>(t4 - t3).count();

        csv << n << "," << std::scientific << std::setprecision(8) << (bb_ms * 1e-3) << ","
            << std::fixed << std::setprecision(3) << dp_ms << "," << bb_ms << "," << bb_nodes << "\n";

        std::cout << std::setw(6) << n 
                  << std::setw(16) << std::fixed << std::setprecision(3) << dp_ms 
                  << std::setw(16) << bb_ms 
                  << std::setw(16) << bb_nodes << "\n";
    }

    csv.close();
    return 0;
}
