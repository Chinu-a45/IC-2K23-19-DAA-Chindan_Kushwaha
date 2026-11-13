/**
 * Unit 4: Dynamic Programming
 * Experiment 7: Traveling Salesperson Problem using Dynamic Programming (Held-Karp)
 * 
 * Recurrence:
 * C(S, j) = min_{i in S, i != j} { C(S \ {j}, i) + dist(i, j) }
 * Time Complexity: O(n^2 2^n), Space Complexity: O(n 2^n).
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

class HeldKarpTSP {
public:
    static constexpr int INF = 1e9;

    static std::pair<int, std::vector<int>> solve(int n, const std::vector<std::vector<int>>& dist) {
        int total_masks = 1 << n;
        std::vector<std::vector<int>> dp(total_masks, std::vector<int>(n, INF));
        std::vector<std::vector<int>> parent(total_masks, std::vector<int>(n, -1));

        // Base case: start from vertex 0
        dp[1][0] = 0;

        for (int mask = 1; mask < total_masks; ++mask) {
            for (int u = 0; u < n; ++u) {
                if (!(mask & (1 << u))) continue;
                if (dp[mask][u] == INF) continue;

                for (int v = 0; v < n; ++v) {
                    if (!(mask & (1 << v))) {
                        int next_mask = mask | (1 << v);
                        int new_cost = dp[mask][u] + dist[u][v];
                        if (new_cost < dp[next_mask][v]) {
                            dp[next_mask][v] = new_cost;
                            parent[next_mask][v] = u;
                        }
                    }
                }
            }
        }

        // Return to start vertex 0
        int min_tour = INF;
        int last_node = -1;
        int full_mask = (1 << n) - 1;

        for (int u = 1; u < n; ++u) {
            int tour_cost = dp[full_mask][u] + dist[u][0];
            if (tour_cost < min_tour) {
                min_tour = tour_cost;
                last_node = u;
            }
        }

        // Reconstruct tour
        std::vector<int> tour;
        int curr_mask = full_mask;
        int curr_node = last_node;

        while (curr_node != -1) {
            tour.push_back(curr_node);
            int prev_node = parent[curr_mask][curr_node];
            curr_mask ^= (1 << curr_node);
            curr_node = prev_node;
        }
        std::reverse(tour.begin(), tour.end());
        tour.push_back(0); // Return to start

        return {min_tour, tour};
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "    Unit 04 - Experiment 07: Held-Karp TSP via DP      \n";
    std::cout << "========================================================\n";

    int n = 4;
    std::vector<std::vector<int>> dist = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    auto res = HeldKarpTSP::solve(n, dist);
    std::cout << "Minimum TSP Tour Cost: " << res.first << " (Expected: 80)\n";
    std::cout << "Optimal Tour: ";
    for (size_t i = 0; i < res.second.size(); ++i) {
        std::cout << res.second[i] << (i + 1 < res.second.size() ? " -> " : "");
    }
    std::cout << "\n";

    // Benchmark for n = 4 to 18
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,time_ms,tour_cost\n";

    std::cout << "\nBenchmark Table (Held-Karp Exponential Scaling):\n";
    std::cout << std::setw(6) << "n" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ms)" 
              << std::setw(16) << "Min Tour Cost" << "\n";
    std::cout << std::string(56, '-') << "\n";

    for (int sz = 4; sz <= 16; sz += 2) {
        std::vector<std::vector<int>> d(sz, std::vector<int>(sz, 0));
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                if (i != j) d[i][j] = (i * 13 + j * 17) % 50 + 5;
            }
        }

        auto start = std::chrono::high_resolution_clock::now();
        auto r = HeldKarpTSP::solve(sz, d);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
        double elapsed_sec = elapsed_ms * 1e-3;

        csv << sz << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << std::fixed << std::setprecision(4) << elapsed_ms << "," << r.first << "\n";

        std::cout << std::setw(6) << sz 
                  << std::setw(18) << std::scientific << std::setprecision(4) << elapsed_sec
                  << std::setw(16) << std::fixed << std::setprecision(4) << elapsed_ms
                  << std::setw(16) << r.first << "\n";
    }

    csv.close();
    return 0;
}
