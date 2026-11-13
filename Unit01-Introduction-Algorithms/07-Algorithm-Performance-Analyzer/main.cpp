/**
 * Unit 1: Introduction to Algorithms & Performance Analysis
 * Experiment 7: APPLICATION - Algorithm Performance Analyzer
 * 
 * Problem: Develop an automated performance analyzer that benchmarks algorithms
 * across different input sizes, compares theoretical complexity against
 * empirical measurements, and computes scaling error metrics.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>
#include <iomanip>

struct BenchmarkPoint {
    int n;
    double measured_time_us;
    double theoretical_linear;
    double theoretical_log;
};

class PerformanceAnalyzer {
public:
    static double measureLinearSearch(int n) {
        std::vector<int> data(n);
        for (int i = 0; i < n; ++i) data[i] = i;
        int target = n - 1; // Worst case

        auto start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i] == target) break;
        }
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::micro>(end - start).count();
    }

    static void runAnalysis() {
        std::vector<int> sizes = {1000, 5000, 10000, 25000, 50000, 100000};
        std::vector<BenchmarkPoint> points;
        std::ofstream csv("results.csv");
        csv << "n,time_seconds,measured_time_us,theoretical_linear,theoretical_log\n";

        std::cout << std::setw(10) << "n"
                  << std::setw(18) << "Measured (us)"
                  << std::setw(20) << "Theory Linear (us)"
                  << std::setw(20) << "Ratio (T/n)" << "\n";
        std::cout << std::string(68, '-') << "\n";

        double c_factor = 0.0;

        // Base calibration on first point
        double base_time = 0;
        for (int i = 0; i < 20; ++i) base_time += measureLinearSearch(sizes[0]);
        base_time /= 20.0;
        c_factor = base_time / sizes[0];

        for (int n : sizes) {
            double total_us = 0;
            const int RUNS = 25;
            for (int r = 0; r < RUNS; ++r) {
                total_us += measureLinearSearch(n);
            }
            double avg_us = total_us / RUNS;
            double theory_lin = c_factor * n;
            double theory_log = c_factor * std::log2(n) * 100;
            double sec = avg_us * 1e-6;

            points.push_back({n, avg_us, theory_lin, theory_log});

            csv << n << "," << std::scientific << std::setprecision(8) << sec << ","
                << std::fixed << std::setprecision(4) << avg_us << ","
                << theory_lin << "," << theory_log << "\n";

            std::cout << std::setw(10) << n
                      << std::setw(18) << std::fixed << std::setprecision(2) << avg_us
                      << std::setw(20) << theory_lin
                      << std::setw(20) << std::setprecision(4) << (avg_us / n) << "\n";
        }
        csv.close();
        std::cout << "\nTheoretical vs Empirical Analysis completed. Data saved to results.csv.\n";
    }
};

int main() {
    std::cout << "===============================================================\n";
    std::cout << "  Unit 01 - Experiment 07: Algorithm Performance Analyzer     \n";
    std::cout << "===============================================================\n";

    PerformanceAnalyzer::runAnalysis();
    return 0;
}
