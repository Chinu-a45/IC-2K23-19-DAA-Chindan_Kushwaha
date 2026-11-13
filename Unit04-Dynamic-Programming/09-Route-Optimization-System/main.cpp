/**
 * Unit 4: Dynamic Programming
 * Experiment 9: APPLICATION - Route Optimization System
 * 
 * Combines Floyd-Warshall (all-pairs shortest paths across road network)
 * with Held-Karp TSP (optimal delivery tour across customer stops).
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

class RouteOptimizer {
public:
    static constexpr int INF = 1e8;

    static void floydWarshall(int V, std::vector<std::vector<int>>& dist) {
        for (int k = 0; k < V; ++k)
            for (int i = 0; i < V; ++i)
                for (int j = 0; j < V; ++j)
                    if (dist[i][k] != INF && dist[k][j] != INF)
                        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
    }

    static std::pair<int, std::vector<int>> tsp(int n, const std::vector<std::vector<int>>& cost) {
        int total_masks = 1 << n;
        std::vector<std::vector<int>> dp(total_masks, std::vector<int>(n, INF));
        std::vector<std::vector<int>> parent(total_masks, std::vector<int>(n, -1));

        dp[1][0] = 0;
        for (int mask = 1; mask < total_masks; ++mask) {
            for (int u = 0; u < n; ++u) {
                if (!(mask & (1 << u)) || dp[mask][u] == INF) continue;
                for (int v = 0; v < n; ++v) {
                    if (!(mask & (1 << v))) {
                        int next_mask = mask | (1 << v);
                        int new_cost = dp[mask][u] + cost[u][v];
                        if (new_cost < dp[next_mask][v]) {
                            dp[next_mask][v] = new_cost;
                            parent[next_mask][v] = u;
                        }
                    }
                }
            }
        }

        int min_tour = INF, last = -1;
        int full = (1 << n) - 1;
        for (int u = 1; u < n; ++u) {
            int tc = dp[full][u] + cost[u][0];
            if (tc < min_tour) {
                min_tour = tc;
                last = u;
            }
        }

        std::vector<int> tour;
        int cur_m = full, cur_n = last;
        while (cur_n != -1) {
            tour.push_back(cur_n);
            int p = parent[cur_m][cur_n];
            cur_m ^= (1 << cur_n);
            cur_n = p;
        }
        std::reverse(tour.begin(), tour.end());
        tour.push_back(0);
        return {min_tour, tour};
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 04 - Experiment 09: Route Optimization System   \n";
    std::cout << "========================================================\n";

    std::vector<std::string> hubs = {
        "Central Depot", "Hub North", "Hub East", "Hub South", "Hub West"
    };
    int V = hubs.size();
    const int INF = RouteOptimizer::INF;

    std::vector<std::vector<int>> road_network = {
        {0,   12,  INF, 25,  INF},
        {12,  0,   18,  INF, 15},
        {INF, 18,  0,   10,  INF},
        {25,  INF, 10,  0,   20},
        {INF, 15,  INF, 20,  0}
    };

    // Step 1: Compute shortest road distances between all distribution hubs
    RouteOptimizer::floydWarshall(V, road_network);

    // Step 2: Solve optimal TSP tour starting and returning to Central Depot (0)
    auto [min_distance, tour] = RouteOptimizer::tsp(V, road_network);

    std::cout << "Optimal Logistics Delivery Route:\n";
    for (size_t i = 0; i < tour.size(); ++i) {
        std::cout << hubs[tour[i]] << (i + 1 < tour.size() ? " -> " : "");
    }
    std::cout << "\nTotal Route Distance: " << min_distance << " km\n";

    // Benchmark across various tour sizes
    std::vector<int> stop_sizes = {4, 6, 8, 10, 12, 14};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,min_distance_km\n";

    for (int n : stop_sizes) {
        std::vector<std::vector<int>> g(n, std::vector<int>(n, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (i != j) g[i][j] = (i * 7 + j * 11) % 40 + 5;

        auto start = std::chrono::high_resolution_clock::now();
        RouteOptimizer::floydWarshall(n, g);
        auto res = RouteOptimizer::tsp(n, g);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_sec = std::chrono::duration<double>(end - start).count();
        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << "," << res.first << "\n";
    }

    csv.close();
    std::cout << "\nOptimization log saved to results.csv.\n";
    return 0;
}
