/**
 * Unit 6: Backtracking
 * Experiment 3: 8-Queens Problem
 * 
 * Computes all 92 distinct solutions on an 8x8 chessboard.
 * Tracks execution time, state-space exploration count, and formats board layouts.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream>
#include <iomanip>

class EightQueens {
public:
    static bool isSafe(const std::vector<int>& board, int row, int col) {
        for (int i = 0; i < row; ++i) {
            if (board[i] == col || std::abs(board[i] - col) == std::abs(i - row))
                return false;
        }
        return true;
    }

    static void solve(int row, std::vector<int>& board, int& solutions, long long& nodes) {
        nodes++;
        if (row == 8) {
            solutions++;
            return;
        }

        for (int col = 0; col < 8; ++col) {
            if (isSafe(board, row, col)) {
                board[row] = col;
                solve(row + 1, board, solutions, nodes);
                board[row] = -1;
            }
        }
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "       Unit 06 - Experiment 03: 8-Queens Problem        \n";
    std::cout << "========================================================\n";

    std::vector<int> board(8, -1);
    int solutions = 0;
    long long nodes = 0;

    auto start = std::chrono::high_resolution_clock::now();
    EightQueens::solve(0, board, solutions, nodes);
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Total Solutions Found: " << solutions << " (Expected: 92)\n";
    std::cout << "Total State-Space Nodes Explored: " << nodes << "\n";
    std::cout << "Execution Time: " << elapsed_ms << " ms\n";

    std::ofstream csv("results.csv");
    csv << "n,solutions,nodes_explored,time_seconds,time_ms\n";
    csv << "8," << solutions << "," << nodes << "," 
        << std::scientific << std::setprecision(8) << (elapsed_ms * 1e-3) << "," 
        << std::fixed << std::setprecision(4) << elapsed_ms << "\n";
    csv.close();

    std::cout << "Output recorded to results.csv.\n";
    return 0;
}
