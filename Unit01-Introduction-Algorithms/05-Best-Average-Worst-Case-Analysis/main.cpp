/**
 * Unit 1: Introduction to Algorithms & Performance Analysis
 * Experiment 5: Best, Average, and Worst Case Complexity Analysis
 * 
 * Problem: Empirically analyze and demonstrate Best, Average, and Worst Case
 * time complexity scenarios on Linear and Binary Search.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <random>

struct CaseAnalysis {
    int comparisons;
    double time_ns;
};

class SearchAnalyzer {
public:
    static CaseAnalysis linearSearch(const std::vector<int>& arr, int target) {
        auto start = std::chrono::high_resolution_clock::now();
        int comps = 0;
        for (size_t i = 0; i < arr.size(); ++i) {
            comps++;
            if (arr[i] == target) break;
        }
        auto end = std::chrono::high_resolution_clock::now();
        double time_ns = std::chrono::duration<double, std::nano>(end - start).count();
        return {comps, time_ns};
    }

    static CaseAnalysis binarySearch(const std::vector<int>& arr, int target) {
        auto start = std::chrono::high_resolution_clock::now();
        int low = 0, high = static_cast<int>(arr.size()) - 1;
        int comps = 0;
        while (low <= high) {
            comps++;
            int mid = low + (high - low) / 2;
            if (arr[mid] == target) break;
            if (arr[mid] < target) low = mid + 1;
            else high = mid - 1;
        }
        auto end = std::chrono::high_resolution_clock::now();
        double time_ns = std::chrono::duration<double, std::nano>(end - start).count();
        return {comps, time_ns};
    }
};

int main() {
    std::cout << "============================================================\n";
    std::cout << "  Unit 01 - Experiment 05: Best, Average, Worst Case Study  \n";
    std::cout << "============================================================\n";

    std::vector<int> sizes = {1000, 5000, 10000, 25000, 50000, 100000};
    std::ofstream csv("results.csv");
    csv << "n,linear_best_ns,linear_avg_ns,linear_worst_ns,binary_best_ns,binary_avg_ns,binary_worst_ns\n";

    std::cout << std::setw(8) << "n"
              << std::setw(15) << "Lin Best(ns)"
              << std::setw(15) << "Lin Avg(ns)"
              << std::setw(15) << "Lin Worst(ns)"
              << std::setw(15) << "Bin Best(ns)"
              << std::setw(15) << "Bin Avg(ns)"
              << std::setw(15) << "Bin Worst(ns)" << "\n";
    std::cout << std::string(98, '-') << "\n";

    for (int n : sizes) {
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) arr[i] = i * 2;

        // Targets:
        int best_target = arr[0];              // Linear best: index 0
        int worst_target = -1;                 // Linear & Binary worst: not present
        int avg_target = arr[n / 2];           // Average case

        int bin_best_target = arr[(n - 1) / 2]; // Binary best: exact mid element

        // Average multiple trials
        const int TRIALS = 100;
        double lb = 0, la = 0, lw = 0, bb = 0, ba = 0, bw = 0;

        for (int t = 0; t < TRIALS; ++t) {
            lb += SearchAnalyzer::linearSearch(arr, best_target).time_ns;
            la += SearchAnalyzer::linearSearch(arr, avg_target).time_ns;
            lw += SearchAnalyzer::linearSearch(arr, worst_target).time_ns;

            bb += SearchAnalyzer::binarySearch(arr, bin_best_target).time_ns;
            ba += SearchAnalyzer::binarySearch(arr, arr[n * 3 / 4]).time_ns;
            bw += SearchAnalyzer::binarySearch(arr, worst_target).time_ns;
        }

        lb /= TRIALS; la /= TRIALS; lw /= TRIALS;
        bb /= TRIALS; ba /= TRIALS; bw /= TRIALS;

        csv << n << "," << lb << "," << la << "," << lw << ","
            << bb << "," << ba << "," << bw << "\n";

        std::cout << std::setw(8) << n
                  << std::setw(15) << std::fixed << std::setprecision(1) << lb
                  << std::setw(15) << la
                  << std::setw(15) << lw
                  << std::setw(15) << bb
                  << std::setw(15) << ba
                  << std::setw(15) << bw << "\n";
    }

    csv.close();
    std::cout << "\nEmpirical data saved to results.csv.\n";
    return 0;
}
