/**
 * Unit 4: Dynamic Programming
 * Experiment 6: Single-Source Shortest Path (Bellman-Ford DP)
 * 
 * Dynamic Programming formulation for general directed graphs with negative weights.
 * Recurrence: d^{(k)}[v] = min(d^{(k-1)}[v], min_{(u, v) in E} (d^{(k-1)}[u] + w(u, v)))
 * Time Complexity: O(V * E), Space Complexity: O(V).
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

struct Edge {
    int u, v, w;
};

class BellmanFordDP {
public:
    static constexpr int INF = 1e8;

    static std::pair<bool, std::vector<int>> solve(int V, int src, const std::vector<Edge>& edges) {
        std::vector<int> dist(V, INF);
        dist[src] = 0;

        // Relax |V| - 1 times
        for (int i = 1; i <= V - 1; ++i) {
            for (const auto& e : edges) {
                if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.w;
                }
            }
        }

        // Check for negative weight cycles
        bool has_neg_cycle = false;
        for (const auto& e : edges) {
            if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                has_neg_cycle = true;
                break;
            }
        }

        return {!has_neg_cycle, dist};
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 04 - Experiment 06: Bellman-Ford Shortest Path   \n";
    std::cout << "========================================================\n";

    int V = 5;
    std::vector<Edge> edges = {
        {0, 1, -1}, {0, 2, 4},
        {1, 2, 3},  {1, 3, 2}, {1, 4, 2},
        {3, 2, 5},  {3, 1, 1},
        {4, 3, -3}
    };

    auto res = BellmanFordDP::solve(V, 0, edges);
    std::cout << "Negative Cycle Detected: " << (res.first ? "No" : "Yes") << "\n";
    std::cout << "Shortest Distances from Source 0:\n";
    for (int i = 0; i < V; ++i) {
        std::cout << "  Vertex " << i << ": " << res.second[i] << "\n";
    }

    // Benchmark across various V
    std::vector<int> sizes = {100, 250, 500, 1000, 1500};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,time_ms\n";

    std::cout << "\nBenchmark Table:\n";
    std::cout << std::setw(10) << "Vertices" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ms)" << "\n";
    std::cout << std::string(44, '-') << "\n";

    for (int n : sizes) {
        std::vector<Edge> test_edges;
        for (int i = 0; i < n; ++i) {
            for (int k = 1; k <= 6; ++k) {
                int j = (i + k) % n;
                test_edges.push_back({i, j, (i * 2 + k * 5) % 40 - 5});
            }
        }

        auto start = std::chrono::high_resolution_clock::now();
        auto r = BellmanFordDP::solve(n, 0, test_edges);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
        double elapsed_sec = elapsed_ms * 1e-3;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << std::fixed << std::setprecision(4) << elapsed_ms << "\n";

        std::cout << std::setw(10) << n 
                  << std::setw(18) << std::scientific << std::setprecision(4) << elapsed_sec
                  << std::setw(16) << std::fixed << std::setprecision(4) << elapsed_ms << "\n";
    }

    csv.close();
    return 0;
}
