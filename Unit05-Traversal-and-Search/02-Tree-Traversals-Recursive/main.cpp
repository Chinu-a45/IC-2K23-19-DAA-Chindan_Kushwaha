/**
 * Unit 5: Traversal & Search Techniques
 * Experiment 2: Recursive Tree Traversals (Preorder, Inorder, Postorder)
 * 
 * Time Complexity: O(n) visiting each node exactly once.
 * Auxiliary Space: O(h) recursion stack where h is tree height.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>

struct Node {
    int val;
    Node* left;
    Node* right;
    explicit Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

class RecursiveTraverser {
public:
    static void preorder(Node* root, std::vector<int>& out) {
        if (!root) return;
        out.push_back(root->val);
        preorder(root->left, out);
        preorder(root->right, out);
    }

    static void inorder(Node* root, std::vector<int>& out) {
        if (!root) return;
        inorder(root->left, out);
        out.push_back(root->val);
        inorder(root->right, out);
    }

    static void postorder(Node* root, std::vector<int>& out) {
        if (!root) return;
        postorder(root->left, out);
        postorder(root->right, out);
        out.push_back(root->val);
    }
};

Node* buildBalancedBST(int start, int end) {
    if (start > end) return nullptr;
    int mid = start + (end - start) / 2;
    Node* root = new Node(mid);
    root->left = buildBalancedBST(start, mid - 1);
    root->right = buildBalancedBST(mid + 1, end);
    return root;
}

int main() {
    std::cout << "========================================================\n";
    std::cout << "  Unit 05 - Experiment 02: Recursive Tree Traversals   \n";
    std::cout << "========================================================\n";

    // Build sample tree with keys 1..7
    Node* root = buildBalancedBST(1, 7);

    std::vector<int> pre, in, post;
    RecursiveTraverser::preorder(root, pre);
    RecursiveTraverser::inorder(root, in);
    RecursiveTraverser::postorder(root, post);

    std::cout << "Preorder  (Root-Left-Right): ";
    for (int x : pre) std::cout << x << " ";
    std::cout << "\nInorder   (Left-Root-Right): ";
    for (int x : in) std::cout << x << " ";
    std::cout << "\nPostorder (Left-Right-Root): ";
    for (int x : post) std::cout << x << " ";
    std::cout << "\n";

    // Benchmark across various tree sizes
    std::vector<int> sizes = {1000, 5000, 10000, 25000, 50000, 100000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,preorder_us,inorder_us,postorder_us\n";

    std::cout << "\nBenchmark Table:\n";
    std::cout << std::setw(10) << "Nodes (n)" 
              << std::setw(18) << "Time (seconds)" 
              << std::setw(16) << "Preorder (us)" 
              << std::setw(16) << "Inorder (us)" 
              << std::setw(16) << "Postorder (us)" << "\n";
    std::cout << std::string(76, '-') << "\n";

    for (int n : sizes) {
        Node* large_tree = buildBalancedBST(1, n);

        std::vector<int> dump;
        dump.reserve(n);

        auto t1 = std::chrono::high_resolution_clock::now();
        RecursiveTraverser::preorder(large_tree, dump);
        auto t2 = std::chrono::high_resolution_clock::now();
        double pre_us = std::chrono::duration<double, std::micro>(t2 - t1).count();

        dump.clear();
        auto t3 = std::chrono::high_resolution_clock::now();
        RecursiveTraverser::inorder(large_tree, dump);
        auto t4 = std::chrono::high_resolution_clock::now();
        double in_us = std::chrono::duration<double, std::micro>(t4 - t3).count();

        dump.clear();
        auto t5 = std::chrono::high_resolution_clock::now();
        RecursiveTraverser::postorder(large_tree, dump);
        auto t6 = std::chrono::high_resolution_clock::now();
        double post_us = std::chrono::duration<double, std::micro>(t6 - t5).count();

        double total_sec = (pre_us + in_us + post_us) * 1e-6;
        csv << n << "," << std::scientific << std::setprecision(8) << total_sec << ","
            << std::fixed << std::setprecision(2) << pre_us << "," << in_us << "," << post_us << "\n";

        std::cout << std::setw(10) << n 
                  << std::setw(18) << std::scientific << std::setprecision(4) << total_sec
                  << std::setw(16) << std::fixed << std::setprecision(2) << pre_us
                  << std::setw(16) << in_us
                  << std::setw(16) << post_us << "\n";
    }

    csv.close();
    return 0;
}
