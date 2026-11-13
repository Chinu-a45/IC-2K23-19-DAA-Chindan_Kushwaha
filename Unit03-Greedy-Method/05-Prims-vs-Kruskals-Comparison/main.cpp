/**
 * Unit 3: Greedy Method
 * Experiment 5: Comparison of Prim's and Kruskal's Algorithms
 * 
 * Compares execution time and scalability on Sparse vs Dense graphs:
 * - Sparse graphs (E ~ V): Kruskal's is often faster due to fewer edges to sort.
 * - Dense graphs (E ~ V^2): Prim's is often preferred.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

struct Edge { int u, v, w; };
struct AdjEdge { int to, w; };

// Prim's
int runPrim(int V, const std::vector<std::vector<AdjEdge>>& adj) {
    std::vector<bool> inMST(V, false);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.push({0, 0});
    int total = 0, count = 0;

    while (!pq.empty() && count < V) {
        auto [w, u] = pq.top();
        pq.pop();
        if (inMST[u]) continue;
        inMST[u] = true;
        total += w;
        count++;

        for (auto& edge : adj[u]) {
            if (!inMST[edge.to]) pq.push({edge.w, edge.to});
        }
    }
    return total;
}

// Kruskal's
struct DSU {
    std::vector<int> p;
    DSU(int n) : p(n) { for (int i = 0; i < n; ++i) p[i] = i; }
    int find(int i) { return p[i] == i ? i : (p[i] = find(p[i])); }
    bool unite(int i, int j) {
        int r1 = find(i), r2 = find(j);
        if (r1 == r2) return false;
        p[r1] = r2;
        return true;
    }
};

int runKruskal(int V, std::vector<Edge>& edges) {
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    DSU dsu(V);
    int total = 0, count = 0;
    for (const auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            total += e.w;
            if (++count == V - 1) break;
        }
    }
    return total;
}

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 03 - Experiment 05: Prim's vs Kruskal's Benchmark\n";
    std::cout << "========================================================\n";

    std::vector<int> sizes = {100, 200, 500, 1000, 1500};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,prims_ms,kruskals_ms\n";

    std::cout << std::setw(10) << "Vertices"
              << std::setw(18) << "Prim's (ms)"
              << std::setw(18) << "Kruskal's (ms)" << "\n";
    std::cout << std::string(46, '-') << "\n";

    for (int V : sizes) {
        std::vector<std::vector<AdjEdge>> adj(V);
        std::vector<Edge> edges;

        // Build connected graph with degree ~ 8
        for (int i = 0; i < V; ++i) {
            for (int k = 1; k <= 4; ++k) {
                int j = (i + k) % V;
                int w = (i * 3 + k * 7) % 100 + 1;
                adj[i].push_back({j, w});
                adj[j].push_back({i, w});
                edges.push_back({i, j, w});
            }
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        int p_cost = runPrim(V, adj);
        auto t2 = std::chrono::high_resolution_clock::now();
        double p_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        int k_cost = runKruskal(V, edges);
        auto t4 = std::chrono::high_resolution_clock::now();
        double k_ms = std::chrono::duration<double, std::milli>(t4 - t3).count();

        csv << V << "," << std::scientific << std::setprecision(8) << (p_ms * 1e-3) << ","
            << std::fixed << std::setprecision(4) << p_ms << "," << k_ms << "\n";

        std::cout << std::setw(10) << V
                  << std::setw(18) << std::fixed << std::setprecision(4) << p_ms
                  << std::setw(18) << k_ms << "\n";
    }

    csv.close();
    std::cout << "\nComparison completed. Data saved to results.csv.\n";
    return 0;
}
