/**
 * Unit 4: Dynamic Programming
 * Experiment 5: All-Pairs Shortest Path (Floyd-Warshall)
 * 
 * Recurrence:
 * D^{(k)}[i][j] = min(D^{(k-1)}[i][j], D^{(k-1)}[i][k] + D^{(k-1)}[k][j])
 * Time Complexity: O(V^3), Space Complexity: O(V^2).
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

class FloydWarshall {
public:
    static constexpr int INF = 1e8;

    static std::vector<std::vector<int>> solve(int V, std::vector<std::vector<int>>& dist) {
        for (int k = 0; k < V; ++k) {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        return dist;
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "   Unit 04 - Experiment 05: Floyd-Warshall Algorithm    \n";
    std::cout << "========================================================\n";

    const int INF = FloydWarshall::INF;
    int V = 4;
    std::vector<std::vector<int>> matrix = {
        {0,   5,   INF, 10},
        {INF, 0,   3,   INF},
        {INF, INF, 0,   1},
        {INF, INF, INF, 0}
    };

    auto result = FloydWarshall::solve(V, matrix);
    std::cout << "Shortest Distance Matrix (4x4):\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (result[i][j] == INF) std::cout << std::setw(6) << "INF";
            else std::cout << std::setw(6) << result[i][j];
        }
        std::cout << "\n";
    }

    // Benchmark across various V
    std::vector<int> sizes = {50, 100, 150, 200, 300};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,time_ms\n";

    std::cout << "\nBenchmark Table:\n";
    std::cout << std::setw(10) << "Vertices" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ms)" << "\n";
    std::cout << std::string(44, '-') << "\n";

    for (int n : sizes) {
        std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
            for (int k = 1; k <= 5; ++k) {
                int j = (i + k) % n;
                dist[i][j] = (i * 2 + k * 3) % 50 + 1;
            }
        }

        auto start = std::chrono::high_resolution_clock::now();
        FloydWarshall::solve(n, dist);
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
