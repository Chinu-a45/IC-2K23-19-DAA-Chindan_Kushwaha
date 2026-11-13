/**
 * Unit 4: Dynamic Programming
 * Experiment 4: Multistage Graph Shortest Path
 * 
 * Dynamic Programming Backward Formulation:
 * cost(i, j) = min { c(j, l) + cost(i + 1, l) } for all edges (j, l)
 * Time Complexity: O(V + E) for DAG.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

struct Edge {
    int to;
    int weight;
};

class MultistageGraph {
public:
    static std::pair<int, std::vector<int>> findShortestPath(
        int num_stages, int total_vertices, const std::vector<std::vector<Edge>>& adj) {
        
        const int INF = 1e9;
        std::vector<int> cost(total_vertices + 1, INF);
        std::vector<int> next_node(total_vertices + 1, -1);

        int sink = total_vertices;
        cost[sink] = 0;

        // Backward DP calculation
        for (int u = total_vertices - 1; u >= 1; --u) {
            for (const auto& edge : adj[u]) {
                int v = edge.to;
                int w = edge.weight;
                if (cost[v] != INF && w + cost[v] < cost[u]) {
                    cost[u] = w + cost[v];
                    next_node[u] = v;
                }
            }
        }

        // Reconstruct path
        std::vector<int> path;
        int curr = 1;
        while (curr != -1) {
            path.push_back(curr);
            curr = next_node[curr];
        }

        return {cost[1], path};
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "     Unit 04 - Experiment 04: Multistage Graph      \n";
    std::cout << "====================================================\n";

    // 4-stage graph, 8 vertices
    // Stage 1: {1}
    // Stage 2: {2, 3, 4}
    // Stage 3: {5, 6, 7}
    // Stage 4: {8} (Sink)
    int V = 8;
    std::vector<std::vector<Edge>> adj(V + 1);

    auto add = [&](int u, int v, int w) { adj[u].push_back({v, w}); };

    add(1, 2, 2); add(1, 3, 1); add(1, 4, 3);
    add(2, 5, 2); add(2, 6, 3);
    add(3, 5, 6); add(3, 6, 7);
    add(4, 5, 6); add(4, 6, 8); add(4, 7, 9);
    add(5, 8, 1); add(6, 8, 4); add(7, 8, 2);

    auto res = MultistageGraph::findShortestPath(4, V, adj);
    std::cout << "Minimum Cost: " << res.first << " (Expected: 5 via 1 -> 2 -> 5 -> 8)\n";
    std::cout << "Optimal Path: ";
    for (size_t i = 0; i < res.second.size(); ++i) {
        std::cout << res.second[i] << (i + 1 < res.second.size() ? " -> " : "");
    }
    std::cout << "\n";

    // Benchmark across various stage/vertex sizes
    std::vector<int> sizes = {50, 100, 250, 500, 1000, 2000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,shortest_cost\n";

    std::cout << "\nBenchmark Table:\n";
    std::cout << std::setw(10) << "Vertices" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ms)" 
              << std::setw(16) << "Min Cost" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (int n : sizes) {
        std::vector<std::vector<Edge>> g(n + 1);
        for (int i = 1; i < n; ++i) {
            for (int k = 1; k <= 3 && i + k <= n; ++k) {
                g[i].push_back({i + k, (i * 3 + k * 5) % 20 + 1});
            }
        }

        auto start = std::chrono::high_resolution_clock::now();
        auto r = MultistageGraph::findShortestPath(10, n, g);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
        double elapsed_sec = elapsed_ms * 1e-3;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << "," << r.first << "\n";

        std::cout << std::setw(10) << n 
                  << std::setw(18) << std::scientific << std::setprecision(4) << elapsed_sec
                  << std::setw(16) << std::fixed << std::setprecision(4) << elapsed_ms
                  << std::setw(16) << r.first << "\n";
    }

    csv.close();
    return 0;
}
