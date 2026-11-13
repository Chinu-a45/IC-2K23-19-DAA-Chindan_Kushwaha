/**
 * Unit 6: Backtracking
 * Experiment 4: N-Queens Problem for Arbitrary N
 * 
 * Analyzes solution count growth and execution scaling from N=4 to N=14.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>
#include <iomanip>

class NQueensSolver {
public:
    static bool isSafe(const std::vector<int>& board, int row, int col) {
        for (int i = 0; i < row; ++i) {
            if (board[i] == col || std::abs(board[i] - col) == std::abs(i - row))
                return false;
        }
        return true;
    }

    static void solve(int row, int N, std::vector<int>& board, long long& count, long long& nodes) {
        nodes++;
        if (row == N) {
            count++;
            return;
        }

        for (int col = 0; col < N; ++col) {
            if (isSafe(board, row, col)) {
                board[row] = col;
                solve(row + 1, N, board, count, nodes);
                board[row] = -1;
            }
        }
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "       Unit 06 - Experiment 04: N-Queens Scalability     \n";
    std::cout << "========================================================\n";

    std::ofstream csv("results.csv");
    csv << "n,time_seconds,solutions,nodes_explored,time_ms\n";

    std::cout << std::setw(6) << "N" 
              << std::setw(14) << "Solutions" 
              << std::setw(18) << "Nodes Explored" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Time (ms)" << "\n";
    std::cout << std::string(72, '-') << "\n";

    for (int N = 4; N <= 12; ++N) {
        std::vector<int> board(N, -1);
        long long count = 0;
        long long nodes = 0;

        auto start = std::chrono::high_resolution_clock::now();
        NQueensSolver::solve(0, N, board, count, nodes);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
        double elapsed_sec = elapsed_ms * 1e-3;

        csv << N << "," << std::scientific << std::setprecision(8) << elapsed_sec << ","
            << count << "," << nodes << "," << std::fixed << std::setprecision(4) << elapsed_ms << "\n";

        std::cout << std::setw(6) << N 
                  << std::setw(14) << count 
                  << std::setw(18) << nodes 
                  << std::setw(18) << std::scientific << std::setprecision(4) << elapsed_sec
                  << std::setw(16) << std::fixed << std::setprecision(4) << elapsed_ms << "\n";
    }

    csv.close();
    return 0;
}
