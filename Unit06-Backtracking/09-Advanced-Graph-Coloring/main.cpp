/**
 * Unit 6: Backtracking
 * Experiment 9: ADVANCED - M-Coloring Problem on Graphs
 * 
 * Determines whether a graph can be colored with at most M colors such that
 * no two adjacent vertices share the same color.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>

class GraphColoring {
public:
    static bool isSafe(int u, int c, const std::vector<std::vector<int>>& adj, const std::vector<int>& color) {
        for (int v : adj[u]) {
            if (color[v] == c) return false;
        }
        return true;
    }

    static bool solve(int u, int V, int m, const std::vector<std::vector<int>>& adj, 
                      std::vector<int>& color, long long& attempts) {
        if (u == V) return true;

        for (int c = 1; c <= m; ++c) {
            attempts++;
            if (isSafe(u, c, adj, color)) {
                color[u] = c;
                if (solve(u + 1, V, m, adj, color, attempts)) return true;
                color[u] = 0;
            }
        }
        return false;
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "    Unit 06 - Experiment 09: M-Coloring on Graphs       \n";
    std::cout << "========================================================\n";

    // Petersen Graph (10 vertices, chromatic number = 3)
    int V = 10;
    std::vector<std::vector<int>> adj(V);
    auto add = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };

    // Outer pentagon
    for (int i = 0; i < 5; ++i) add(i, (i + 1) % 5);
    // Inner star
    for (int i = 0; i < 5; ++i) add(5 + i, 5 + ((i + 2) % 5));
    // Radial spokes
    for (int i = 0; i < 5; ++i) add(i, 5 + i);

    std::vector<int> color(V, 0);
    long long attempts = 0;
    int m = 3;

    bool ok = GraphColoring::solve(0, V, m, adj, color, attempts);
    std::cout << "Can Petersen Graph be colored with " << m << " colors? " << (ok ? "YES" : "NO") << "\n";
    std::cout << "Vertex Colors: [ ";
    for (int c : color) std::cout << c << " ";
    std::cout << "]\n";
    std::cout << "Coloring decisions evaluated: " << attempts << "\n";

    // Benchmark across various vertex sizes
    std::ofstream csv("results.csv");
    csv << "V,m,time_seconds,attempts\n";

    for (int test_v : {6, 8, 10, 12, 14}) {
        std::vector<std::vector<int>> g(test_v);
        for (int i = 0; i < test_v; ++i) {
            g[i].push_back((i + 1) % test_v);
            g[(i + 1) % test_v].push_back(i);
            g[i].push_back((i + 2) % test_v);
            g[(i + 2) % test_v].push_back(i);
        }
        std::vector<int> col(test_v, 0);
        long long att = 0;
        auto start = std::chrono::high_resolution_clock::now();
        GraphColoring::solve(0, test_v, 3, g, col, att);
        auto end = std::chrono::high_resolution_clock::now();
        double elapsed_sec = std::chrono::duration<double>(end - start).count();

        csv << test_v << ",3," << std::scientific << std::setprecision(8) << elapsed_sec << "," << att << "\n";
    }

    csv.close();
    return 0;
}
