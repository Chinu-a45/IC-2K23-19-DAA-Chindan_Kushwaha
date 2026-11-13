/**
 * Unit 6: Backtracking
 * Experiment 2: 4-Queens Problem
 * 
 * Step-by-step state-space tree exploration for N=4.
 * Demonstrates row-by-row queen placement, column/diagonal checks, and backtracking on dead ends.
 */

#include <iostream>
#include <vector>
#include <cmath>

class FourQueens {
public:
    static bool isSafe(const std::vector<int>& board, int row, int col) {
        for (int i = 0; i < row; ++i) {
            if (board[i] == col || std::abs(board[i] - col) == std::abs(i - row)) {
                return false;
            }
        }
        return true;
    }

    static void solve(int row, std::vector<int>& board, int& solution_count, int& dead_ends) {
        if (row == 4) {
            solution_count++;
            std::cout << "\n>>> SOLUTION #" << solution_count << " Found <<<\n";
            printBoard(board);
            return;
        }

        for (int col = 0; col < 4; ++col) {
            if (isSafe(board, row, col)) {
                board[row] = col;
                solve(row + 1, board, solution_count, dead_ends);
                // Backtrack
                board[row] = -1;
            } else {
                dead_ends++;
            }
        }
    }

    static void printBoard(const std::vector<int>& board) {
        for (int r = 0; r < 4; ++r) {
            std::cout << "  ";
            for (int c = 0; c < 4; ++c) {
                if (board[r] == c) std::cout << " Q ";
                else std::cout << " . ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "       Unit 06 - Experiment 02: 4-Queens Problem        \n";
    std::cout << "========================================================\n";

    std::vector<int> board(4, -1);
    int solutions = 0;
    int dead_ends = 0;

    FourQueens::solve(0, board, solutions, dead_ends);

    std::cout << "\nTotal Solutions Found: " << solutions << " (Expected: 2)\n";
    std::cout << "Dead-End States Pruned: " << dead_ends << "\n";
    return 0;
}
