/**
 * Unit 5: Traversal & Search Techniques
 * Experiment 3: Iterative Tree Traversals (Preorder, Inorder, Postorder)
 * 
 * Uses explicit std::stack to eliminate call stack overhead and prevent recursion depth limits.
 * Time Complexity: O(n), Space Complexity: O(h).
 */

#include <iostream>
#include <vector>
#include <stack>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <algorithm>

struct Node {
    int val;
    Node* left;
    Node* right;
    explicit Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

class IterativeTraverser {
public:
    static std::vector<int> preorder(Node* root) {
        std::vector<int> res;
        if (!root) return res;
        std::stack<Node*> st;
        st.push(root);

        while (!st.empty()) {
            Node* curr = st.top();
            st.pop();
            res.push_back(curr->val);
            if (curr->right) st.push(curr->right);
            if (curr->left) st.push(curr->left);
        }
        return res;
    }

    static std::vector<int> inorder(Node* root) {
        std::vector<int> res;
        std::stack<Node*> st;
        Node* curr = root;

        while (curr != nullptr || !st.empty()) {
            while (curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top();
            st.pop();
            res.push_back(curr->val);
            curr = curr->right;
        }
        return res;
    }

    static std::vector<int> postorder(Node* root) {
        std::vector<int> res;
        if (!root) return res;
        std::stack<Node*> s1, s2;
        s1.push(root);

        while (!s1.empty()) {
            Node* curr = s1.top();
            s1.pop();
            s2.push(curr);
            if (curr->left) s1.push(curr->left);
            if (curr->right) s1.push(curr->right);
        }
        while (!s2.empty()) {
            res.push_back(s2.top()->val);
            s2.pop();
        }
        return res;
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
    std::cout << "  Unit 05 - Experiment 03: Iterative Tree Traversals   \n";
    std::cout << "========================================================\n";

    Node* root = buildBalancedBST(1, 7);

    auto pre = IterativeTraverser::preorder(root);
    auto in = IterativeTraverser::inorder(root);
    auto post = IterativeTraverser::postorder(root);

    std::cout << "Iterative Preorder : ";
    for (int x : pre) std::cout << x << " ";
    std::cout << "\nIterative Inorder  : ";
    for (int x : in) std::cout << x << " ";
    std::cout << "\nIterative Postorder: ";
    for (int x : post) std::cout << x << " ";
    std::cout << "\n";

    // Benchmark across sizes
    std::vector<int> sizes = {1000, 5000, 10000, 25000, 50000, 100000};
    std::ofstream csv("results.csv");
    csv << "n,time_seconds,preorder_us,inorder_us,postorder_us\n";

    for (int n : sizes) {
        Node* large_tree = buildBalancedBST(1, n);

        auto t1 = std::chrono::high_resolution_clock::now();
        auto r1 = IterativeTraverser::preorder(large_tree);
        auto t2 = std::chrono::high_resolution_clock::now();
        double pre_us = std::chrono::duration<double, std::micro>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        auto r2 = IterativeTraverser::inorder(large_tree);
        auto t4 = std::chrono::high_resolution_clock::now();
        double in_us = std::chrono::duration<double, std::micro>(t4 - t3).count();

        auto t5 = std::chrono::high_resolution_clock::now();
        auto r3 = IterativeTraverser::postorder(large_tree);
        auto t6 = std::chrono::high_resolution_clock::now();
        double post_us = std::chrono::duration<double, std::micro>(t6 - t5).count();

        double total_sec = (pre_us + in_us + post_us) * 1e-6;
        csv << n << "," << std::scientific << std::setprecision(8) << total_sec << ","
            << std::fixed << std::setprecision(2) << pre_us << "," << in_us << "," << post_us << "\n";
    }

    csv.close();
    std::cout << "\nIterative traversal benchmarks saved to results.csv.\n";
    return 0;
}
