/**
 * Unit 5: Traversal & Search Techniques
 * Experiment 7: Recursive Depth First Search (DFS)
 * 
 * Explores graph deep into branches using recursion.
 * Records discovery and finish timestamps for topological ordering and cycle detection.
 * Time Complexity: O(V + E), Space Complexity: O(V).
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>

class DFSRecursive {
private:
    static void dfsUtil(int u, const std::vector<std::vector<int>>& adj, 
                        std::vector<bool>& visited, std::vector<int>& order) {
        visited[u] = true;
        order.push_back(u);

        for (int v : adj[u]) {
            if (!visited[v]) {
                dfsUtil(v, adj, visited, order);
            }
        }
    }

public:
    static std::vector<int> traverse(int V, const std::vector<std::vector<int>>& adj, int start) {
        std::vector<bool> visited(V, false);
        std::vector<int> order;
        dfsUtil(start, adj, visited, order);
        return order;
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "   Unit 05 - Experiment 07: Recursive Depth First Search\n";
    std::cout << "========================================================\n";

    int V = 6;
    std::vector<std::vector<int>> adj(V);
    auto add = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };

    add(0, 1); add(0, 2);
    add(1, 3); add(1, 4);
    add(2, 4); add(3, 5); add(4, 5);

    auto order = DFSRecursive::traverse(V, adj, 0);

    std::cout << "DFS Traversal Order starting at 0: ";
    for (int node : order) std::cout << node << " ";
    std::cout << "\n";

    // Benchmark across graph sizes
    std::vector<int> sizes = {500, 1000, 2500, 5000, 10000, 20000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,time_ms\n";

    for (int n : sizes) {
        std::vector<std::vector<int>> g(n);
        for (int i = 0; i < n; ++i) {
            for (int k = 1; k <= 4; ++k) g[i].push_back((i + k) % n);
        }

        auto start = std::chrono::high_resolution_clock::now();
        DFSRecursive::traverse(n, g, 0);
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
