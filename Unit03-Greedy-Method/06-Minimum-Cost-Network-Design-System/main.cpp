/**
 * Unit 3: Greedy Method
 * Experiment 6: APPLICATION - Minimum-Cost Network Design System
 * 
 * Problem: Design a regional telecommunication network connecting cities
 * with minimum fiber-optic cable deployment cost, calculating redundancy,
 * latency bounds, and total cable investment.
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

struct City {
    int id;
    std::string name;
    double x, y; // 2D coordinates in kilometers
};

struct CableLink {
    int cityA, cityB;
    double length_km;
    double cost_usd;
};

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

class NetworkDesigner {
public:
    static double distance(const City& c1, const City& c2) {
        return std::hypot(c1.x - c2.x, c1.y - c2.y);
    }

    static std::pair<double, std::vector<CableLink>> designBackbone(
        const std::vector<City>& cities, double cost_per_km) {
        
        int n = cities.size();
        std::vector<CableLink> all_links;

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double dist = distance(cities[i], cities[j]);
                all_links.push_back({i, j, dist, dist * cost_per_km});
            }
        }

        std::sort(all_links.begin(), all_links.end(), [](const CableLink& a, const CableLink& b) {
            return a.cost_usd < b.cost_usd;
        });

        DSU dsu(n);
        double total_cost = 0.0;
        std::vector<CableLink> backbone;

        for (const auto& link : all_links) {
            if (dsu.unite(link.cityA, link.cityB)) {
                total_cost += link.cost_usd;
                backbone.push_back(link);
                if (backbone.size() == static_cast<size_t>(n - 1)) break;
            }
        }
        return {total_cost, backbone};
    }
};

int main() {
    std::cout << "===============================================================\n";
    std::cout << "  Unit 03 - Experiment 06: Minimum-Cost Network Design System  \n";
    std::cout << "===============================================================\n";

    std::vector<City> regional_cities = {
        {0, "Indore", 0.0, 0.0},
        {1, "Bhopal", 190.0, 15.0},
        {2, "Ujjain", 20.0, 55.0},
        {3, "Dewas", 35.0, 10.0},
        {4, "Gwalior", 210.0, 310.0},
        {5, "Jabalpur", 340.0, 40.0}
    };

    const double COST_PER_KM = 3500.0; // $3,500 per km fiber cable
    auto [total_cost, backbone] = NetworkDesigner::designBackbone(regional_cities, COST_PER_KM);

    std::cout << "Optimal Telecommunication Network Backbone:\n";
    std::cout << std::string(60, '-') << "\n";
    double total_length = 0;
    for (const auto& link : backbone) {
        std::cout << "  " << regional_cities[link.cityA].name 
                  << " <---> " << regional_cities[link.cityB].name 
                  << " | " << std::fixed << std::setprecision(1) << link.length_km << " km"
                  << " | $" << std::fixed << std::setprecision(0) << link.cost_usd << "\n";
        total_length += link.length_km;
    }
    std::cout << std::string(60, '-') << "\n";
    std::cout << "Total Fiber Length: " << total_length << " km\n";
    std::cout << "Total Capital Investment: $" << total_cost << "\n";

    // Benchmark across different network node sizes
    std::vector<int> node_sizes = {20, 50, 100, 200, 500};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,total_cost_usd,total_length_km\n";

    for (int n : node_sizes) {
        std::vector<City> synth_cities;
        for (int i = 0; i < n; ++i) {
            synth_cities.push_back({i, "Node_" + std::to_string(i), (i * 37) % 500 * 1.0, (i * 59) % 500 * 1.0});
        }
        auto start = std::chrono::high_resolution_clock::now();
        auto res = NetworkDesigner::designBackbone(synth_cities, COST_PER_KM);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_sec = std::chrono::duration<double>(end - start).count();
        double len = 0;
        for (auto& l : res.second) len += l.length_km;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << std::fixed << std::setprecision(2) << res.first << "," << len << "\n";
    }

    csv.close();
    std::cout << "\nNetwork design benchmarking complete. Output saved to results.csv.\n";
    return 0;
}
