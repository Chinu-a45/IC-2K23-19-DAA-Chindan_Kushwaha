/**
 * Unit 6: Backtracking
 * Experiment 5: Sum of Subsets Problem
 * 
 * Bounding Conditions:
 * 1. current_sum + w[k] <= target
 * 2. current_sum + remaining_sum >= target (prunes branches where even taking all remaining items cannot reach target)
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

class SumOfSubsets {
public:
    static void findSubsets(int k, int current_sum, int remaining_sum, int target,
                            const std::vector<int>& w, std::vector<int>& x,
                            std::vector<std::vector<int>>& solutions, long long& nodes) {
        nodes++;
        x[k] = 1;

        if (current_sum + w[k] == target) {
            std::vector<int> sol;
            for (size_t i = 0; i <= static_cast<size_t>(k); ++i) {
                if (x[i]) sol.push_back(w[i]);
            }
            solutions.push_back(sol);
        } else if (k + 1 < static_cast<int>(w.size()) && current_sum + w[k] + w[k + 1] <= target) {
            findSubsets(k + 1, current_sum + w[k], remaining_sum - w[k], target, w, x, solutions, nodes);
        }

        // Branch without w[k]
        x[k] = 0;
        if (k + 1 < static_cast<int>(w.size()) && 
            current_sum + remaining_sum - w[k] >= target && 
            current_sum + w[k + 1] <= target) {
            findSubsets(k + 1, current_sum, remaining_sum - w[k], target, w, x, solutions, nodes);
        }
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "       Unit 06 - Experiment 05: Sum of Subsets          \n";
    std::cout << "========================================================\n";

    std::vector<int> w = {5, 10, 12, 13, 15, 18};
    int target = 30;
    std::sort(w.begin(), w.end());

    int total_sum = std::accumulate(w.begin(), w.end(), 0);
    std::vector<int> x(w.size(), 0);
    std::vector<std::vector<int>> solutions;
    long long nodes = 0;

    SumOfSubsets::findSubsets(0, 0, total_sum, target, w, x, solutions, nodes);

    std::cout << "Target Sum: " << target << "\n";
    std::cout << "Valid Subsets:\n";
    for (const auto& s : solutions) {
        std::cout << "  { ";
        for (int v : s) std::cout << v << " ";
        std::cout << "}\n";
    }
    std::cout << "Nodes Explored: " << nodes << "\n";

    // Benchmark across various instance sizes
    std::vector<int> sizes = {10, 15, 20, 25, 28};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,nodes_explored,solutions_count\n";

    for (int n : sizes) {
        std::vector<int> test_w(n);
        for (int i = 0; i < n; ++i) test_w[i] = (i + 1) * 3;
        int t_sum = std::accumulate(test_w.begin(), test_w.end(), 0);
        int t = t_sum / 3;

        std::vector<int> t_x(n, 0);
        std::vector<std::vector<int>> t_sols;
        long long t_nodes = 0;

        auto start = std::chrono::high_resolution_clock::now();
        SumOfSubsets::findSubsets(0, 0, t_sum, t, test_w, t_x, t_sols, t_nodes);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_sec = std::chrono::duration<double>(end - start).count();
        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << t_nodes << "," << t_sols.size() << "\n";
    }

    csv.close();
    std::cout << "Output recorded to results.csv.\n";
    return 0;
}
