/**
 * Unit 5: Traversal & Search Techniques
 * Experiment 4: Graph Representation using Adjacency Matrix
 * 
 * Space Complexity: O(V^2)
 * Edge Check: O(1)
 * Iterate Neighbors: O(V)
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>

class GraphAdjMatrix {
private:
    int V;
    std::vector<std::vector<int>> matrix;

public:
    explicit GraphAdjMatrix(int vertices) : V(vertices), matrix(vertices, std::vector<int>(vertices, 0)) {}

    void addEdge(int u, int v, int weight = 1) {
        if (u >= 0 && u < V && v >= 0 && v < V) {
            matrix[u][v] = weight;
            matrix[v][u] = weight; // Undirected
        }
    }

    bool hasEdge(int u, int v) const {
        return (u >= 0 && u < V && v >= 0 && v < V && matrix[u][v] != 0);
    }

    int degree(int u) const {
        int deg = 0;
        for (int j = 0; j < V; ++j) {
            if (matrix[u][j] != 0) deg++;
        }
        return deg;
    }

    void print() const {
        std::cout << "Adjacency Matrix (" << V << "x" << V << "):\n";
        for (int i = 0; i < V; ++i) {
            std::cout << "  [ ";
            for (int j = 0; j < V; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << "]\n";
        }
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 05 - Experiment 04: Graph Adjacency Matrix       \n";
    std::cout << "========================================================\n";

    GraphAdjMatrix g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.print();
    std::cout << "Degree of vertex 1: " << g.degree(1) << " (Expected: 4)\n";
    std::cout << "Edge (0, 4) exists: " << (g.hasEdge(0, 4) ? "Yes" : "No") << "\n";
    std::cout << "Edge (0, 2) exists: " << (g.hasEdge(0, 2) ? "Yes" : "No") << "\n";

    // Benchmark across various V
    std::vector<int> sizes = {100, 250, 500, 1000, 2000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,memory_kb\n";

    for (int n : sizes) {
        auto start = std::chrono::high_resolution_clock::now();
        GraphAdjMatrix test_g(n);
        for (int i = 0; i < n; ++i) test_g.addEdge(i, (i + 1) % n);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_sec = std::chrono::duration<double>(end - start).count();
        double mem_kb = (static_cast<double>(n) * n * sizeof(int)) / 1024.0;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << std::fixed << std::setprecision(1) << mem_kb << "\n";
    }

    csv.close();
    std::cout << "\nResults recorded to results.csv.\n";
    return 0;
}
