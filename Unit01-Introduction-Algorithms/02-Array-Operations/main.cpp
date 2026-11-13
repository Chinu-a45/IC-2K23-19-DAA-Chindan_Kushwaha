/**
 * Unit 1: Introduction to Algorithms & Performance Analysis
 * Experiment 2: Basic Operations on Arrays
 * 
 * Problem: Implement insertion, deletion, traversal, update, and search on an array.
 * Includes complete input validation, dynamic boundary checking, and step-by-step reporting.
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

class DynamicArray {
private:
    std::vector<int> data;

public:
    DynamicArray() = default;
    explicit DynamicArray(const std::vector<int>& initial) : data(initial) {}

    size_t size() const { return data.size(); }

    void traverse(const std::string& label = "Array State") const {
        std::cout << label << " (Size: " << data.size() << "): [";
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i] << (i + 1 < data.size() ? ", " : "");
        }
        std::cout << "]\n";
    }

    void insertAt(size_t pos, int val) {
        if (pos > data.size()) {
            throw std::out_of_range("Insert position out of bounds: pos=" + std::to_string(pos) + 
                                    ", max allowed=" + std::to_string(data.size()));
        }
        data.insert(data.begin() + pos, val);
        std::cout << "-> Inserted " << val << " at index " << pos << ".\n";
    }

    int deleteAt(size_t pos) {
        if (pos >= data.size()) {
            throw std::out_of_range("Delete position out of bounds: pos=" + std::to_string(pos) + 
                                    ", current size=" + std::to_string(data.size()));
        }
        int removed = data[pos];
        data.erase(data.begin() + pos);
        std::cout << "-> Deleted element " << removed << " from index " << pos << ".\n";
        return removed;
    }

    void updateAt(size_t pos, int newVal) {
        if (pos >= data.size()) {
            throw std::out_of_range("Update position out of bounds: pos=" + std::to_string(pos) + 
                                    ", current size=" + std::to_string(data.size()));
        }
        int oldVal = data[pos];
        data[pos] = newVal;
        std::cout << "-> Updated index " << pos << " from " << oldVal << " to " << newVal << ".\n";
    }

    int search(int val) const {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i] == val) return static_cast<int>(i);
        }
        return -1;
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "    Unit 01 - Experiment 02: Array Operations       \n";
    std::cout << "====================================================\n";

    try {
        DynamicArray arr({10, 20, 30, 40, 50});
        arr.traverse("Initial Array");

        // 1. Insertion
        arr.insertAt(2, 99);
        arr.traverse("After Inserting 99 at index 2");

        // 2. Update
        arr.updateAt(4, 77);
        arr.traverse("After Updating index 4 to 77");

        // 3. Search
        int target = 77;
        int idx = arr.search(target);
        std::cout << "-> Search for " << target << ": " 
                  << (idx != -1 ? "Found at index " + std::to_string(idx) : "Not found") << "\n";

        // 4. Deletion
        arr.deleteAt(1);
        arr.traverse("After Deleting element at index 1");

        // 5. Bounds Check Demonstration
        std::cout << "\nDemonstrating bounds checking on invalid index (pos=100):\n";
        try {
            arr.deleteAt(100);
        } catch (const std::out_of_range& e) {
            std::cout << "Caught expected exception: " << e.what() << "\n";
        }

        std::cout << "\nFinal verification successful.\n";
    } catch (const std::exception& ex) {
        std::cerr << "Fatal Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
