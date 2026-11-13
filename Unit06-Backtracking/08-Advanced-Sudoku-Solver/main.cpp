/**
 * Unit 6: Backtracking
 * Experiment 8: ADVANCED - 9x9 Sudoku Solver
 * 
 * Backtracking solver with row, column, and 3x3 block constraint propagation.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>

class SudokuSolver {
public:
    static bool isSafe(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
        for (int x = 0; x < 9; ++x) {
            if (grid[row][x] == num || grid[x][col] == num) return false;
        }
        int startRow = row - row % 3, startCol = col - col % 3;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (grid[i + startRow][j + startCol] == num) return false;
            }
        }
        return true;
    }

    static bool solve(std::vector<std::vector<int>>& grid, long long& step_count) {
        int row = -1, col = -1;
        bool isEmpty = false;

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (grid[i][j] == 0) {
                    row = i; col = j;
                    isEmpty = true;
                    break;
                }
            }
            if (isEmpty) break;
        }

        if (!isEmpty) return true; // Puzzle solved

        for (int num = 1; num <= 9; ++num) {
            step_count++;
            if (isSafe(grid, row, col, num)) {
                grid[row][col] = num;
                if (solve(grid, step_count)) return true;
                grid[row][col] = 0; // Backtrack
            }
        }
        return false;
    }

    static void printGrid(const std::vector<std::vector<int>>& grid) {
        for (int r = 0; r < 9; ++r) {
            if (r % 3 == 0 && r != 0) std::cout << "  ------+-------+------\n";
            std::cout << "  ";
            for (int c = 0; c < 9; ++c) {
                if (c % 3 == 0 && c != 0) std::cout << "| ";
                std::cout << grid[r][c] << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "       Unit 06 - Experiment 08: 9x9 Sudoku Solver       \n";
    std::cout << "========================================================\n";

    std::vector<std::vector<int>> puzzle = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    std::cout << "Initial Sudoku Puzzle:\n";
    SudokuSolver::printGrid(puzzle);

    long long steps = 0;
    auto start = std::chrono::high_resolution_clock::now();
    bool solved = SudokuSolver::solve(puzzle, steps);
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "\nSolved Sudoku Grid (" << steps << " decision steps, " << elapsed_ms << " ms):\n";
    if (solved) SudokuSolver::printGrid(puzzle);

    std::ofstream csv("results.csv");
    csv << "n,time_seconds,decision_steps,time_ms\n";
    csv << "81," << std::scientific << std::setprecision(8) << (elapsed_ms * 1e-3) << ","
        << steps << "," << std::fixed << std::setprecision(4) << elapsed_ms << "\n";
    csv.close();

    return 0;
}
