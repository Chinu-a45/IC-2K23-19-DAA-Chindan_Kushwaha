/**
 * Unit 5: Traversal & Search Techniques
 * Experiment 5: Graph Representation using Adjacency List
 * 
 * Space Complexity: O(V + E)
 * Iterate Neighbors: O(deg(u)) optimal for sparse graphs.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>

class GraphAdjList {
private:
    int V;
    std::vector<std::vector<int>> adj;

public:
    explicit GraphAdjList(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            adj[u].push_back(v);
            adj[v].push_back(u); // Undirected
        }
    }

    int degree(int u) const {
        return static_cast<int>(adj[u].size());
    }

    void print() const {
        std::cout << "Adjacency List Representation:\n";
        for (int i = 0; i < V; ++i) {
            std::cout << "  Vertex " << i << " -> [ ";
            for (int neighbor : adj[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << "]\n";
        }
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "    Unit 05 - Experiment 05: Graph Adjacency List      \n";
    std::cout << "========================================================\n";

    GraphAdjList g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.print();
    std::cout << "Degree of vertex 1: " << g.degree(1) << " (Expected: 4)\n";

    // Benchmark across various V
    std::vector<int> sizes = {100, 500, 1000, 5000, 10000, 25000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,memory_kb\n";

    for (int n : sizes) {
        auto start = std::chrono::high_resolution_clock::now();
        GraphAdjList test_g(n);
        for (int i = 0; i < n; ++i) test_g.addEdge(i, (i + 1) % n);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_sec = std::chrono::duration<double>(end - start).count();
        double mem_kb = (static_cast<double>(n) * 2 * sizeof(int)) / 1024.0;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << std::fixed << std::setprecision(1) << mem_kb << "\n";
    }

    csv.close();
    std::cout << "\nResults recorded to results.csv.\n";
    return 0;
}
