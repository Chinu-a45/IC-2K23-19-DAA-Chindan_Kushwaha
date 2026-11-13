/**
 * Unit 5: Traversal & Search Techniques
 * Experiment 6: Breadth First Search (BFS)
 * 
 * Traverses vertices level by level using a queue. Computes shortest hops in unweighted graphs.
 * Time Complexity: O(V + E), Space Complexity: O(V).
 */

#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <fstream>
#include <iomanip>

class BFSGraph {
public:
    static std::pair<std::vector<int>, std::vector<int>> runBFS(int V, const std::vector<std::vector<int>>& adj, int start) {
        std::vector<bool> visited(V, false);
        std::vector<int> distance(V, -1);
        std::vector<int> order;
        std::queue<int> q;

        visited[start] = true;
        distance[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    distance[v] = distance[u] + 1;
                    q.push(v);
                }
            }
        }
        return {order, distance};
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "      Unit 05 - Experiment 06: Breadth First Search     \n";
    std::cout << "========================================================\n";

    int V = 6;
    std::vector<std::vector<int>> adj(V);
    auto add = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };

    add(0, 1); add(0, 2);
    add(1, 3); add(1, 4);
    add(2, 4); add(3, 5); add(4, 5);

    auto [order, dist] = BFSGraph::runBFS(V, adj, 0);

    std::cout << "BFS Traversal Order starting at 0: ";
    for (int node : order) std::cout << node << " ";
    std::cout << "\n\nShortest Distances from 0:\n";
    for (int i = 0; i < V; ++i) {
        std::cout << "  Vertex " << i << ": " << dist[i] << " hops\n";
    }

    // Benchmark across sizes
    std::vector<int> sizes = {500, 1000, 2500, 5000, 10000, 25000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,time_ms\n";

    for (int n : sizes) {
        std::vector<std::vector<int>> g(n);
        for (int i = 0; i < n; ++i) {
            for (int k = 1; k <= 4; ++k) g[i].push_back((i + k) % n);
        }

        auto start = std::chrono::high_resolution_clock::now();
        BFSGraph::runBFS(n, g, 0);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
        double elapsed_sec = elapsed_ms * 1e-3;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << std::fixed << std::setprecision(4) << elapsed_ms << "\n";
    }

    csv.close();
    std::cout << "\nBenchmark recorded to results.csv.\n";
    return 0;
}
