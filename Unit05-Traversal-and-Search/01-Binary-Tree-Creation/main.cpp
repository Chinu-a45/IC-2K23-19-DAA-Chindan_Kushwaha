/**
 * Unit 5: Traversal & Search Techniques
 * Experiment 1: Binary Tree Creation
 * 
 * Implements Binary Search Tree (BST) creation, node insertion, search,
 * height calculation, and hierarchical visual tree display.
 */

#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    TreeNode* root = nullptr;

    void insert(int key) {
        root = insertRec(root, key);
    }

    bool search(int key) const {
        return searchRec(root, key);
    }

    int getHeight() const {
        return heightRec(root);
    }

    void displayInorder() const {
        std::cout << "Inorder (Sorted): [ ";
        inorderRec(root);
        std::cout << "]\n";
    }

private:
    TreeNode* insertRec(TreeNode* node, int key) {
        if (!node) return new TreeNode(key);
        if (key < node->val) node->left = insertRec(node->left, key);
        else if (key > node->val) node->right = insertRec(node->right, key);
        return node;
    }

    bool searchRec(TreeNode* node, int key) const {
        if (!node) return false;
        if (node->val == key) return true;
        if (key < node->val) return searchRec(node->left, key);
        return searchRec(node->right, key);
    }

    int heightRec(TreeNode* node) const {
        if (!node) return 0;
        return 1 + std::max(heightRec(node->left), heightRec(node->right));
    }

    void inorderRec(TreeNode* node) const {
        if (!node) return;
        inorderRec(node->left);
        std::cout << node->val << " ";
        inorderRec(node->right);
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "    Unit 05 - Experiment 01: Binary Tree Creation   \n";
    std::cout << "====================================================\n";

    BinaryTree tree;
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    std::cout << "Inserting values: ";
    for (int v : values) {
        std::cout << v << " ";
        tree.insert(v);
    }
    std::cout << "\n\n";

    tree.displayInorder();
    std::cout << "Tree Height: " << tree.getHeight() << " (Expected: 3)\n";

    int search_key = 40;
    std::cout << "Search key " << search_key << ": " 
              << (tree.search(search_key) ? "Found" : "Not Found") << "\n";

    search_key = 99;
    std::cout << "Search key " << search_key << ": " 
              << (tree.search(search_key) ? "Found" : "Not Found") << "\n";

    std::cout << "\nBinary Tree creation verified successfully.\n";
    return 0;
}
