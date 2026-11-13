/**
 * Unit 5: Traversal & Search Techniques
 * Experiment 10: Adjacency Matrix vs Adjacency List Comparison
 * 
 * Evaluates memory allocation and neighbor enumeration speeds on Sparse vs Dense graphs.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 05 - Experiment 10: Matrix vs List Benchmark     \n";
    std::cout << "========================================================\n";

    std::vector<int> sizes = {100, 250, 500, 1000, 2000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,matrix_mem_kb,list_mem_kb,matrix_scan_us,list_scan_us\n";

    std::cout << std::setw(8) << "V"
              << std::setw(16) << "Matrix Mem(KB)"
              << std::setw(16) << "List Mem(KB)"
              << std::setw(18) << "Matrix Scan(us)"
              << std::setw(18) << "List Scan(us)" << "\n";
    std::cout << std::string(76, '-') << "\n";

    for (int V : sizes) {
        int degree = 10; // Sparse graph

        // 1. Matrix
        std::vector<std::vector<int>> mat(V, std::vector<int>(V, 0));
        for (int i = 0; i < V; ++i) {
            for (int k = 1; k <= degree; ++k) mat[i][(i + k) % V] = 1;
        }

        // 2. List
        std::vector<std::vector<int>> adj(V);
        for (int i = 0; i < V; ++i) {
            for (int k = 1; k <= degree; ++k) adj[i].push_back((i + k) % V);
        }

        // Scan all neighbors
        auto t1 = std::chrono::high_resolution_clock::now();
        long long sum_m = 0;
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (mat[i][j]) sum_m += j;
            }
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        double mat_us = std::chrono::duration<double, std::micro>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        long long sum_l = 0;
        for (int i = 0; i < V; ++i) {
            for (int v : adj[i]) {
                sum_l += v;
            }
        }
        auto t4 = std::chrono::high_resolution_clock::now();
        double list_us = std::chrono::duration<double, std::micro>(t4 - t3).count();

        double mat_kb = (static_cast<double>(V) * V * sizeof(int)) / 1024.0;
        double list_kb = (static_cast<double>(V) * sizeof(std::vector<int>) + 
                          static_cast<double>(V) * degree * sizeof(int)) / 1024.0;

        csv << V << "," << std::scientific << std::setprecision(8) << (mat_us * 1e-6) << ","
            << std::fixed << std::setprecision(1) << mat_kb << "," << list_kb << ","
            << mat_us << "," << list_us << "\n";

        std::cout << std::setw(8) << V
                  << std::setw(16) << std::fixed << std::setprecision(1) << mat_kb
                  << std::setw(16) << list_kb
                  << std::setw(18) << std::fixed << std::setprecision(2) << mat_us
                  << std::setw(18) << list_us << "\n";
    }

    csv.close();
    return 0;
}
