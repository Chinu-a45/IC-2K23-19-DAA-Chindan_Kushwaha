/**
 * Unit 5: Traversal & Search Techniques
 * Experiment 9: Comparison of BFS and DFS
 * 
 * Side-by-side benchmark comparing BFS (Queue-based) vs DFS (Stack-based)
 * on execution time, traversal path lengths, and memory depth.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>
#include <fstream>
#include <iomanip>

int runBFS(int V, const std::vector<std::vector<int>>& adj, int s) {
    std::vector<bool> vis(V, false);
    std::queue<int> q;
    q.push(s); vis[s] = true;
    int visited_count = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        visited_count++;
        for (int v : adj[u]) {
            if (!vis[v]) { vis[v] = true; q.push(v); }
        }
    }
    return visited_count;
}

int runDFS(int V, const std::vector<std::vector<int>>& adj, int s) {
    std::vector<bool> vis(V, false);
    std::stack<int> st;
    st.push(s);
    int visited_count = 0;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (!vis[u]) {
            vis[u] = true;
            visited_count++;
            for (int v : adj[u]) {
                if (!vis[v]) st.push(v);
            }
        }
    }
    return visited_count;
}

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 05 - Experiment 09: BFS vs DFS Comparative Study \n";
    std::cout << "========================================================\n";

    std::vector<int> sizes = {500, 1000, 2500, 5000, 10000, 20000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,bfs_ms,dfs_ms\n";

    std::cout << std::setw(10) << "Vertices"
              << std::setw(18) << "BFS (ms)"
              << std::setw(18) << "DFS (ms)" << "\n";
    std::cout << std::string(46, '-') << "\n";

    for (int n : sizes) {
        std::vector<std::vector<int>> g(n);
        for (int i = 0; i < n; ++i) {
            for (int k = 1; k <= 5; ++k) g[i].push_back((i + k) % n);
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        runBFS(n, g, 0);
        auto t2 = std::chrono::high_resolution_clock::now();
        double bfs_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        runDFS(n, g, 0);
        auto t4 = std::chrono::high_resolution_clock::now();
        double dfs_ms = std::chrono::duration<double, std::milli>(t4 - t3).count();

        csv << n << "," << std::scientific << std::setprecision(8) << (bfs_ms * 1e-3) << ","
            << std::fixed << std::setprecision(4) << bfs_ms << "," << dfs_ms << "\n";

        std::cout << std::setw(10) << n
                  << std::setw(18) << std::fixed << std::setprecision(4) << bfs_ms
                  << std::setw(18) << dfs_ms << "\n";
    }

    csv.close();
    std::cout << "\nComparison complete. Output written to results.csv.\n";
    return 0;
}
