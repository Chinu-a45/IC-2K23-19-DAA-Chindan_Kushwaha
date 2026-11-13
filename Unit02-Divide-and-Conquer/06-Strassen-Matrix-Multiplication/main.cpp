/**
 * Unit 2: Divide and Conquer
 * Experiment 6: Strassen's Matrix Multiplication
 * 
 * Problem: Multiply two n x n matrices using 7 submatrix multiplications instead of 8.
 * Recurrence: T(n) = 7T(n/2) + O(n^2) => T(n) = O(n^{log_2 7}) ~ O(n^{2.807})
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>

using Matrix = std::vector<std::vector<int>>;

class MatrixUtils {
public:
    static Matrix create(int n) {
        return Matrix(n, std::vector<int>(n, 0));
    }

    static Matrix add(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C = create(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                C[i][j] = A[i][j] + B[i][j];
        return C;
    }

    static Matrix subtract(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C = create(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                C[i][j] = A[i][j] - B[i][j];
        return C;
    }

    static Matrix standardMultiply(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C = create(n);
        for (int i = 0; i < n; ++i)
            for (int k = 0; k < n; ++k)
                for (int j = 0; j < n; ++j)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }

    static Matrix strassenMultiply(const Matrix& A, const Matrix& B) {
        int n = A.size();
        if (n <= 2) {
            return standardMultiply(A, B);
        }

        int k = n / 2;
        Matrix A11 = create(k), A12 = create(k), A21 = create(k), A22 = create(k);
        Matrix B11 = create(k), B12 = create(k), B21 = create(k), B22 = create(k);

        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + k];
                A21[i][j] = A[i + k][j];
                A22[i][j] = A[i + k][j + k];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + k];
                B21[i][j] = B[i + k][j];
                B22[i][j] = B[i + k][j + k];
            }
        }

        // 7 Strassen products
        Matrix M1 = strassenMultiply(add(A11, A22), add(B11, B22));
        Matrix M2 = strassenMultiply(add(A21, A22), B11);
        Matrix M3 = strassenMultiply(A11, subtract(B12, B22));
        Matrix M4 = strassenMultiply(A22, subtract(B21, B11));
        Matrix M5 = strassenMultiply(add(A11, A12), B22);
        Matrix M6 = strassenMultiply(subtract(A21, A11), add(B11, B12));
        Matrix M7 = strassenMultiply(subtract(A12, A22), add(B21, B22));

        // Combine to C submatrices
        Matrix C11 = add(subtract(add(M1, M4), M5), M7);
        Matrix C12 = add(M3, M5);
        Matrix C21 = add(M2, M4);
        Matrix C22 = add(add(subtract(M1, M2), M3), M6);

        Matrix C = create(n);
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                C[i][j] = C11[i][j];
                C[i][j + k] = C12[i][j];
                C[i + k][j] = C21[i][j];
                C[i + k][j + k] = C22[i][j];
            }
        }
        return C;
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 02 - Experiment 06: Strassen Matrix Multiplier   \n";
    std::cout << "========================================================\n";

    int n = 4;
    Matrix A = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 1, 2, 3},
        {4, 5, 6, 7}
    };
    Matrix B = {
        {8, 7, 6, 5},
        {4, 3, 2, 1},
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };

    Matrix C_std = MatrixUtils::standardMultiply(A, B);
    Matrix C_str = MatrixUtils::strassenMultiply(A, B);

    bool match = true;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (C_std[i][j] != C_str[i][j]) match = false;

    std::cout << "Strassen 4x4 verification vs Standard: " << (match ? "PASSED" : "FAILED") << "\n";
    std::cout << "Result Matrix C (4x4):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << std::setw(6) << C_str[i][j];
        }
        std::cout << "\n";
    }

    // Benchmark across 2^k sizes: 4, 8, 16, 32, 64, 128
    std::vector<int> test_sizes = {4, 8, 16, 32, 64, 128};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,strassen_ms,standard_ms\n";

    std::cout << "\nEmpirical Performance Comparison (Strassen vs Standard):\n";
    std::cout << std::setw(8) << "n" 
              << std::setw(18) << "Strassen (ms)" 
              << std::setw(18) << "Standard (ms)" << "\n";
    std::cout << std::string(44, '-') << "\n";

    for (int sz : test_sizes) {
        Matrix Mat1 = MatrixUtils::create(sz);
        Matrix Mat2 = MatrixUtils::create(sz);
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                Mat1[i][j] = (i + j) % 10;
                Mat2[i][j] = (i * j + 1) % 10;
            }
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        Matrix R1 = MatrixUtils::strassenMultiply(Mat1, Mat2);
        auto t2 = std::chrono::high_resolution_clock::now();
        double str_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        Matrix R2 = MatrixUtils::standardMultiply(Mat1, Mat2);
        auto t4 = std::chrono::high_resolution_clock::now();
        double std_ms = std::chrono::duration<double, std::milli>(t4 - t3).count();

        csv << sz << "," << std::scientific << std::setprecision(8) << (str_ms * 1e-3) << ","
            << std::fixed << std::setprecision(4) << str_ms << "," << std_ms << "\n";

        std::cout << std::setw(8) << sz 
                  << std::setw(18) << std::fixed << std::setprecision(4) << str_ms
                  << std::setw(18) << std_ms << "\n";
    }

    csv.close();
    return 0;
}
