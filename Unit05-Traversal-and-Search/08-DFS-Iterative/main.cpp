/**
 * Unit 5: Traversal & Search Techniques
 * Experiment 8: Iterative Depth First Search (DFS)
 * 
 * Uses an explicit std::stack to perform depth-first traversal without call stack depth limits.
 * Time Complexity: O(V + E), Space Complexity: O(V).
 */

#include <iostream>
#include <vector>
#include <stack>
#include <chrono>
#include <fstream>
#include <iomanip>

class DFSIterative {
public:
    static std::vector<int> traverse(int V, const std::vector<std::vector<int>>& adj, int start) {
        std::vector<bool> visited(V, false);
        std::vector<int> order;
        std::stack<int> st;

        st.push(start);

        while (!st.empty()) {
            int u = st.top();
            st.pop();

            if (!visited[u]) {
                visited[u] = true;
                order.push_back(u);

                // Push neighbors in reverse order to mimic recursive order
                for (auto it = adj[u].rbegin(); it != adj[u].rend(); ++it) {
                    if (!visited[*it]) {
                        st.push(*it);
                    }
                }
            }
        }
        return order;
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "   Unit 05 - Experiment 08: Iterative Depth First Search\n";
    std::cout << "========================================================\n";

    int V = 6;
    std::vector<std::vector<int>> adj(V);
    auto add = [&](int u, int v) { adj[u].push_back(v); adj[v].push_back(u); };

    add(0, 1); add(0, 2);
    add(1, 3); add(1, 4);
    add(2, 4); add(3, 5); add(4, 5);

    auto order = DFSIterative::traverse(V, adj, 0);

    std::cout << "Iterative DFS Traversal Order: ";
    for (int node : order) std::cout << node << " ";
    std::cout << "\n";

    // Benchmark across sizes
    std::vector<int> sizes = {500, 1000, 2500, 5000, 10000, 20000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,time_ms\n";

    for (int n : sizes) {
        std::vector<std::vector<int>> g(n);
        for (int i = 0; i < n; ++i) {
            for (int k = 1; k <= 4; ++k) g[i].push_back((i + k) % n);
        }

        auto start = std::chrono::high_resolution_clock::now();
        DFSIterative::traverse(n, g, 0);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
        double elapsed_sec = elapsed_ms * 1e-3;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << std::fixed << std::setprecision(4) << elapsed_ms << "\n";
    }

    csv.close();
    std::cout << "\nBenchmark recorded to results.csv.\n";
    return 0;
}
