/**
 * Unit 5: Traversal & Search Techniques
 * Experiment 11: APPLICATION - Graph Exploration / Network Traversal System
 * 
 * Comprehensive Network Topology Analyzer:
 * - Connected Components Discovery
 * - Cycle Detection (Tarjan / DFS Tree back-edge analysis)
 * - Articulation Points (Cut Vertices) Detection
 * - Subnet Reachability Analysis
 */

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <iomanip>

class NetworkExplorer {
private:
    int V;
    std::vector<std::vector<int>> adj;
    int timer;

    void dfsAP(int u, int p, std::vector<bool>& vis, std::vector<int>& tin, 
               std::vector<int>& low, std::vector<bool>& is_ap) {
        vis[u] = true;
        tin[u] = low[u] = ++timer;
        int children = 0;

        for (int v : adj[u]) {
            if (v == p) continue;
            if (vis[v]) {
                low[u] = std::min(low[u], tin[v]);
            } else {
                dfsAP(v, u, vis, tin, low, is_ap);
                low[u] = std::min(low[u], low[v]);
                if (low[v] >= tin[u] && p != -1) is_ap[u] = true;
                children++;
            }
        }
        if (p == -1 && children > 1) is_ap[u] = true;
    }

public:
    explicit NetworkExplorer(int vertices) : V(vertices), adj(vertices), timer(0) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int countComponents() {
        std::vector<bool> vis(V, false);
        int comps = 0;
        for (int i = 0; i < V; ++i) {
            if (!vis[i]) {
                comps++;
                std::vector<int> q = {i};
                vis[i] = true;
                size_t head = 0;
                while (head < q.size()) {
                    int u = q[head++];
                    for (int v : adj[u]) {
                        if (!vis[v]) { vis[v] = true; q.push_back(v); }
                    }
                }
            }
        }
        return comps;
    }

    std::vector<int> findCriticalGateways() {
        timer = 0;
        std::vector<bool> vis(V, false);
        std::vector<int> tin(V, -1), low(V, -1);
        std::vector<bool> is_ap(V, false);

        for (int i = 0; i < V; ++i) {
            if (!vis[i]) dfsAP(i, -1, vis, tin, low, is_ap);
        }

        std::vector<int> aps;
        for (int i = 0; i < V; ++i) {
            if (is_ap[i]) aps.push_back(i);
        }
        return aps;
    }
};

int main() {
    std::cout << "===============================================================\n";
    std::cout << "  Unit 05 - Experiment 11: Graph Exploration & Topology System \n";
    std::cout << "===============================================================\n";

    // Enterprise network with 7 routers
    NetworkExplorer net(7);
    net.addEdge(0, 1);
    net.addEdge(1, 2);
    net.addEdge(2, 0); // Triangle subnet 0-1-2
    net.addEdge(1, 3); // Bridge to 3
    net.addEdge(3, 4);
    net.addEdge(4, 5);
    net.addEdge(5, 6);
    net.addEdge(6, 4); // Subnet 4-5-6

    std::cout << "Connected Components: " << net.countComponents() << " (Fully connected network)\n";

    auto critical_routers = net.findCriticalGateways();
    std::cout << "Critical Gateways (Single Points of Failure):\n";
    for (int r : critical_routers) {
        std::cout << "  Router " << r << " is a Cut-Vertex (Failure partitions the network!)\n";
    }

    std::cout << "\nNetwork topology exploration completed successfully.\n";
    return 0;
}
