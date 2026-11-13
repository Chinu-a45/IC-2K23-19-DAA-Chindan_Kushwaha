/**
 * Unit 7: NP-Hard, NP-Complete & Advanced Optimization
 * Experiment 3: TSP using Branch and Bound
 * 
 * Uses Reduced Cost Matrix (Row and Column reductions) to compute lower bounds
 * and explores search tree using best-first strategy.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

class TSPBranchBound {
public:
    static constexpr int INF = 1e8;

    struct Node {
        std::vector<std::vector<int>> matrix;
        std::vector<int> path;
        int level;
        int vertex;
        int cost;

        bool operator>(const Node& other) const {
            return cost > other.cost; // Min-heap
        }
    };

    static int reduceMatrix(int n, std::vector<std::vector<int>>& mat) {
        int reduction_cost = 0;

        // Row reduction
        for (int i = 0; i < n; ++i) {
            int min_val = INF;
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] < min_val) min_val = mat[i][j];
            }
            if (min_val != INF && min_val > 0) {
                reduction_cost += min_val;
                for (int j = 0; j < n; ++j) {
                    if (mat[i][j] != INF) mat[i][j] -= min_val;
                }
            }
        }

        // Column reduction
        for (int j = 0; j < n; ++j) {
            int min_val = INF;
            for (int i = 0; i < n; ++i) {
                if (mat[i][j] < min_val) min_val = mat[i][j];
            }
            if (min_val != INF && min_val > 0) {
                reduction_cost += min_val;
                for (int i = 0; i < n; ++i) {
                    if (mat[i][j] != INF) mat[i][j] -= min_val;
                }
            }
        }

        return reduction_cost;
    }

    static std::pair<int, long long> solve(int n, std::vector<std::vector<int>> cost_matrix) {
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

        Node root;
        root.matrix = cost_matrix;
        root.path = {0};
        root.level = 0;
        root.vertex = 0;
        root.cost = reduceMatrix(n, root.matrix);

        pq.push(root);
        long long nodes_visited = 0;
        int min_tour_cost = INF;

        while (!pq.empty()) {
            Node curr = pq.top();
            pq.pop();
            nodes_visited++;

            if (curr.cost >= min_tour_cost) continue;

            if (curr.level == n - 1) {
                int return_cost = cost_matrix[curr.vertex][0];
                if (return_cost != INF && curr.cost + return_cost < min_tour_cost) {
                    min_tour_cost = curr.cost + return_cost;
                }
                continue;
            }

            for (int v = 0; v < n; ++v) {
                if (curr.matrix[curr.vertex][v] != INF) {
                    Node child;
                    child.matrix = curr.matrix;
                    child.path = curr.path;
                    child.path.push_back(v);
                    child.level = curr.level + 1;
                    child.vertex = v;

                    // Set row curr.vertex and col v to INF
                    for (int j = 0; j < n; ++j) child.matrix[curr.vertex][j] = INF;
                    for (int i = 0; i < n; ++i) child.matrix[i][v] = INF;
                    child.matrix[v][0] = INF; // Prevent early cycle

                    child.cost = curr.cost + curr.matrix[curr.vertex][v] + reduceMatrix(n, child.matrix);

                    if (child.cost < min_tour_cost) {
                        pq.push(child);
                    }
                }
            }
        }

        return {min_tour_cost, nodes_visited};
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "     Unit 07 - Experiment 03: TSP Branch & Bound        \n";
    std::cout << "========================================================\n";

    const int INF = TSPBranchBound::INF;
    int n = 4;
    std::vector<std::vector<int>> cost = {
        {INF, 10,  15,  20},
        {10,  INF, 35,  25},
        {15,  35,  INF, 30},
        {20,  25,  30,  INF}
    };

    auto [tour_cost, nodes] = TSPBranchBound::solve(n, cost);
    std::cout << "Optimal TSP Tour Cost: " << tour_cost << " (Expected: 80)\n";
    std::cout << "Branch and Bound Nodes Visited: " << nodes << "\n";

    // Benchmark across various small n
    std::vector<int> sizes = {4, 6, 8, 10, 12};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,nodes_explored,tour_cost\n";

    for (int sz : sizes) {
        std::vector<std::vector<int>> mat(sz, std::vector<int>(sz, INF));
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                if (i != j) mat[i][j] = (i * 7 + j * 13) % 40 + 5;
            }
        }

        auto start = std::chrono::high_resolution_clock::now();
        auto r = TSPBranchBound::solve(sz, mat);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_sec = std::chrono::duration<double>(end - start).count();
        csv << sz << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << r.second << "," << r.first << "\n";
    }

    csv.close();
    std::cout << "Output recorded to results.csv.\n";
    return 0;
}
