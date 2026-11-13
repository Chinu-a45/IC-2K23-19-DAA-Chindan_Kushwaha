/**
 * Unit 3: Greedy Method
 * Experiment 2: Job Sequencing with Deadlines
 * 
 * Strategy: Sort jobs in descending order of profit.
 * For each job, greedily assign the latest free slot before or at its deadline.
 * Time Complexity: O(n log n) sorting + O(n * min(n, max_deadline)) scheduling.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

struct Job {
    char id;
    int deadline;
    int profit;
};

class JobSequencing {
public:
    static std::pair<int, std::vector<char>> schedule(std::vector<Job>& jobs) {
        std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
            return a.profit > b.profit;
        });

        int max_deadline = 0;
        for (const auto& j : jobs) {
            if (j.deadline > max_deadline) max_deadline = j.deadline;
        }

        std::vector<char> slot(max_deadline + 1, '-');
        int total_profit = 0;

        for (const auto& job : jobs) {
            for (int t = job.deadline; t > 0; --t) {
                if (slot[t] == '-') {
                    slot[t] = job.id;
                    total_profit += job.profit;
                    break;
                }
            }
        }

        std::vector<char> sequence;
        for (int t = 1; t <= max_deadline; ++t) {
            if (slot[t] != '-') sequence.push_back(slot[t]);
        }
        return {total_profit, sequence};
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 03 - Experiment 02: Job Sequencing with Deadlines\n";
    std::cout << "========================================================\n";

    std::vector<Job> sample_jobs = {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    auto res = JobSequencing::schedule(sample_jobs);
    std::cout << "Scheduled Jobs: ";
    for (char c : res.second) std::cout << c << " ";
    std::cout << "\nTotal Profit: " << res.first << " (Expected: 142)\n";

    // Benchmark across various job counts
    std::vector<int> sizes = {500, 1000, 2000, 5000, 10000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,total_profit\n";

    std::cout << "\nBenchmark Table:\n";
    std::cout << std::setw(10) << "n" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ms)" 
              << std::setw(16) << "Profit" << "\n";
    std::cout << std::string(60, '-') << "\n";

    for (int n : sizes) {
        std::vector<Job> jobs;
        jobs.reserve(n);
        for (int i = 0; i < n; ++i) {
            jobs.push_back({static_cast<char>('A' + (i % 26)), 1 + (i % (n / 5 + 1)), 10 + (i % 500)});
        }

        auto start = std::chrono::high_resolution_clock::now();
        auto r = JobSequencing::schedule(jobs);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
        double elapsed_sec = elapsed_ms * 1e-3;

        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << r.first << "\n";

        std::cout << std::setw(10) << n 
                  << std::setw(18) << std::scientific << std::setprecision(4) << elapsed_sec
                  << std::setw(16) << std::fixed << std::setprecision(4) << elapsed_ms
                  << std::setw(16) << r.first << "\n";
    }

    csv.close();
    return 0;
}
