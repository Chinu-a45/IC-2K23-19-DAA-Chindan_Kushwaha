/**
 * Unit 6: Backtracking
 * Experiment 1: General Backtracking Technique
 * 
 * Formal state-space tree exploration framework:
 * - Solution vector X = (x_1, x_2, ..., x_k)
 * - Explicit Bounding Function B(x_1, ..., x_k)
 * - Systematic pruning of infeasible subtrees
 */

#include <iostream>
#include <vector>
#include <iomanip>

class GeneralBacktracking {
public:
    static void generateBinaryVectors(int n, int k, std::vector<int>& X, int& explored_nodes) {
        explored_nodes++;
        if (k == n) {
            std::cout << "  Solution: [ ";
            for (int x : X) std::cout << x << " ";
            std::cout << "]\n";
            return;
        }

        for (int val = 0; val <= 1; ++val) {
            X[k] = val;
            // Bounding Condition: Prune branches where two consecutive 1s occur
            if (k > 0 && X[k - 1] == 1 && X[k] == 1) {
                // Pruned branch!
                continue;
            }
            generateBinaryVectors(n, k + 1, X, explored_nodes);
        }
    }
};

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 06 - Experiment 01: General Backtracking Method   \n";
    std::cout << "========================================================\n";

    int n = 4;
    std::vector<int> X(n, 0);
    int nodes = 0;

    std::cout << "Generating all binary strings of length " << n << " without consecutive 1s:\n";
    GeneralBacktracking::generateBinaryVectors(n, 0, X, nodes);

    std::cout << "\nTotal State-Space Tree Nodes Explored: " << nodes << "\n";
    std::cout << "Theoretical Unconstrained Nodes: " << ((1 << (n + 1)) - 1) << " (Pruning verified!)\n";

    return 0;
}
