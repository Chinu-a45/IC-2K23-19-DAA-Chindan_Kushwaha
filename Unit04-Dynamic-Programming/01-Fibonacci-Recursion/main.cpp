/**
 * Unit 4: Dynamic Programming
 * Experiment 1: Fibonacci using Recursion
 * 
 * Recurrence: F(n) = F(n-1) + F(n-2) with F(0)=0, F(1)=1
 * Time Complexity: O(2^n) exponential due to overlapping subproblems.
 * Space Complexity: O(n) call stack.
 */

#include <iostream>
#include <chrono>
#include <fstream>
#include <iomanip>

class RecursiveFibonacci {
public:
    static long long fib(int n, long long& call_count) {
        call_count++;
        if (n <= 0) return 0;
        if (n == 1) return 1;
        return fib(n - 1, call_count) + fib(n - 2, call_count);
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "    Unit 04 - Experiment 01: Recursive Fibonacci    \n";
    std::cout << "====================================================\n";

    long long count = 0;
    int test_n = 10;
    long long val = RecursiveFibonacci::fib(test_n, count);
    std::cout << "F(" << test_n << ") = " << val << " | Recursive calls: " << count << "\n";

    // Benchmark up to n = 40 (exponential scaling)
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,call_count\n";

    std::cout << "\nBenchmark Table (Exponential Time Demonstration):\n";
    std::cout << std::setw(6) << "n" 
              << std::setw(15) << "F(n)" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(18) << "Recursive Calls" << "\n";
    std::cout << std::string(57, '-') << "\n";

    for (int n = 10; n <= 38; n += 4) {
        count = 0;
        auto start = std::chrono::high_resolution_clock::now();
        long long f = RecursiveFibonacci::fib(n, count);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_sec = std::chrono::duration<double>(end - start).count();
        csv << n << "," << std::scientific << std::setprecision(8) << elapsed_sec << "," << count << "\n";

        std::cout << std::setw(6) << n 
                  << std::setw(15) << f 
                  << std::setw(18) << std::scientific << std::setprecision(4) << elapsed_sec 
                  << std::setw(18) << count << "\n";
    }

    csv.close();
    return 0;
}
