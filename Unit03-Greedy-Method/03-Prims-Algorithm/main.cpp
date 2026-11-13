/**
 * Unit 3: Greedy Method
 * Experiment 3: Minimum Cost Spanning Tree - Prim's Algorithm
 * 
 * Strategy: Grow a single tree from an arbitrary root vertex by greedily adding
 * the cheapest edge connecting an in-tree vertex to an out-of-tree vertex.
 * Time Complexity: O(V^2) with matrix / O(E log V) with adjacency list and min-heap.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <fstream>
#include <iomanip>

struct Edge {
    int to;
    int weight;
};

class PrimsAlgorithm {
public:
    static std::pair<int, std::vector<std::pair<int, int>>> findMST(int V, const std::vector<std::vector<Edge>>& adj) {
        std::vector<bool> inMST(V, false);
        std::vector<int> key(V, 1e9);
        std::vector<int> parent(V, -1);

        // Min-heap: {key[u], u}
        std::priority_queue<std::pair<int, int>, 
                            std::vector<std::pair<int, int>>, 
                            std::greater<std::pair<int, int>>> pq;

        key[0] = 0;
        pq.push({0, 0});

        int total_weight = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            int w = pq.top().first;
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;
            total_weight += w;

            for (const auto& edge : adj[u]) {
                int v = edge.to;
                int weight = edge.weight;

                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({key[v], v});
                }
            }
        }

        std::vector<std::pair<int, int>> mst_edges;
        for (int v = 1; v < V; ++v) {
            if (parent[v] != -1) mst_edges.push_back({parent[v], v});
        }
        return {total_weight, mst_edges};
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "      Unit 03 - Experiment 03: Prim's Algorithm     \n";
    std::cout << "====================================================\n";

    int V = 5;
    std::vector<std::vector<Edge>> adj(V);
    auto add_edge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    };

    add_edge(0, 1, 2);
    add_edge(0, 3, 6);
    add_edge(1, 2, 3);
    add_edge(1, 3, 8);
    add_edge(1, 4, 5);
    add_edge(2, 4, 7);
    add_edge(3, 4, 9);

    auto result = PrimsAlgorithm::findMST(V, adj);
    std::cout << "Minimum Spanning Tree Cost: " << result.first << " (Expected: 16)\n";
    std::cout << "Edges in MST:\n";
    for (auto& e : result.second) {
        std::cout << "  " << e.first << " -- " << e.second << "\n";
    }

    // Benchmark across various graph sizes
    std::vector<int> vertex_sizes = {100, 250, 500, 1000, 2000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,mst_cost\n";

    std::cout << "\nBenchmark Table:\n";
    std::cout << std::setw(10) << "Vertices" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ms)" 
              << std::setw(16) << "MST Cost" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (int n : vertex_sizes) {
        std::vector<std::vector<Edge>> g(n);
        for (int i = 0; i < n; ++i) {
            for (int k = 1; k <= 5; ++k) {
                int j = (i + k) % n;
                int w = 1 + (i * k + 7) % 50;
                g[i].push_back({j, w});
                g[j].push_back({i, w});
            }
        }

        auto start = std::chrono::high_resolution_clock::now();
        auto r = PrimsAlgorithm::findMST(n, g);
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
