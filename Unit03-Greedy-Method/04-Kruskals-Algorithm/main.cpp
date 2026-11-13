/**
 * Unit 3: Greedy Method
 * Experiment 4: Minimum Cost Spanning Tree - Kruskal's Algorithm
 * 
 * Strategy: Sort all edges in non-decreasing order of weight. Greedily pick the
 * smallest edge that does not form a cycle using Disjoint Set Union (DSU)
 * with path compression and union by rank.
 * Time Complexity: O(E log E) = O(E log V).
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

struct Edge {
    int u, v, weight;
};

class DSU {
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    explicit DSU(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i == root_j) return false;

        if (rank[root_i] < rank[root_j]) {
            parent[root_i] = root_j;
        } else if (rank[root_i] > rank[root_j]) {
            parent[root_j] = root_i;
        } else {
            parent[root_j] = root_i;
            rank[root_i]++;
        }
        return true;
    }
};

class KruskalsAlgorithm {
public:
    static std::pair<int, std::vector<Edge>> findMST(int V, std::vector<Edge>& edges) {
        std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        });

        DSU dsu(V);
        int total_cost = 0;
        std::vector<Edge> mst_edges;

        for (const auto& edge : edges) {
            if (dsu.unite(edge.u, edge.v)) {
                total_cost += edge.weight;
                mst_edges.push_back(edge);
                if (mst_edges.size() == static_cast<size_t>(V - 1)) break;
            }
        }
        return {total_cost, mst_edges};
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "    Unit 03 - Experiment 04: Kruskal's Algorithm    \n";
    std::cout << "====================================================\n";

    int V = 4;
    std::vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    auto result = KruskalsAlgorithm::findMST(V, edges);
    std::cout << "Minimum Spanning Tree Cost: " << result.first << " (Expected: 19)\n";
    std::cout << "Edges in MST:\n";
    for (auto& e : result.second) {
        std::cout << "  " << e.u << " -- " << e.v << " (weight: " << e.weight << ")\n";
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
        std::vector<Edge> test_edges;
        for (int i = 0; i < n; ++i) {
            for (int k = 1; k <= 5; ++k) {
                int j = (i + k) % n;
                int w = 1 + (i * k + 7) % 50;
                test_edges.push_back({i, j, w});
            }
        }

        auto start = std::chrono::high_resolution_clock::now();
        auto r = KruskalsAlgorithm::findMST(n, test_edges);
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
