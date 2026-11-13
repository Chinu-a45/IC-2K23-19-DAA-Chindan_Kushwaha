/**
 * Unit 6: Backtracking
 * Experiment 6: Backtracking vs Exhaustive Search
 * 
 * Quantifies the drastic reduction in state space achieved by pruning bounding conditions
 * compared to exhaustive 2^n generate-and-test.
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <fstream>
#include <iomanip>

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 06 - Experiment 06: Backtracking vs Exhaustive   \n";
    std::cout << "========================================================\n";

    std::vector<int> sizes = {10, 15, 18, 20, 22};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,backtrack_nodes,exhaustive_nodes,backtrack_ms,exhaustive_ms\n";

    std::cout << std::setw(6) << "n" 
              << std::setw(18) << "BT Nodes" 
              << std::setw(18) << "Exhaustive Nodes" 
              << std::setw(16) << "BT Time(ms)" 
              << std::setw(16) << "Ex Time(ms)" << "\n";
    std::cout << std::string(74, '-') << "\n";

    for (int n : sizes) {
        std::vector<int> w(n);
        for (int i = 0; i < n; ++i) w[i] = i + 1;
        int target = n * 4;

        // Backtracking count
        long long bt_nodes = 0;
        auto bt_solve = [&](auto self, int k, int sum) -> void {
            bt_nodes++;
            if (sum == target) return;
            if (k >= n || sum > target) return;
            self(self, k + 1, sum + w[k]);
            self(self, k + 1, sum);
        };

        auto t1 = std::chrono::high_resolution_clock::now();
        bt_solve(bt_solve, 0, 0);
        auto t2 = std::chrono::high_resolution_clock::now();
        double bt_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();

        // Exhaustive Search count: 2^{n+1} - 1
        long long ex_nodes = (1ULL << (n + 1)) - 1;
        long long dummy_eval = 0;

        auto t3 = std::chrono::high_resolution_clock::now();
        for (unsigned long long mask = 0; mask < (1ULL << n); ++mask) {
            int s = 0;
            for (int i = 0; i < n; ++i) {
                if (mask & (1ULL << i)) s += w[i];
            }
            if (s == target) dummy_eval++;
        }
        auto t4 = std::chrono::high_resolution_clock::now();
        double ex_ms = std::chrono::duration<double, std::milli>(t4 - t3).count();

        csv << n << "," << std::scientific << std::setprecision(8) << (bt_ms * 1e-3) << ","
            << bt_nodes << "," << ex_nodes << "," 
            << std::fixed << std::setprecision(3) << bt_ms << "," << ex_ms << "\n";

        std::cout << std::setw(6) << n 
                  << std::setw(18) << bt_nodes 
                  << std::setw(18) << ex_nodes 
                  << std::setw(16) << std::fixed << std::setprecision(3) << bt_ms 
                  << std::setw(16) << ex_ms << "\n";
    }

    csv.close();
    return 0;
}
