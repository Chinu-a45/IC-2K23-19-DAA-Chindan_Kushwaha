/**
 * Unit 1: Introduction to Algorithms & Performance Analysis
 * Experiment 1: Algorithm Using Pseudocode and Flowchart
 * 
 * Problem: Implement an algorithm designed via structured pseudocode and flowchart.
 * Demonstrates Euclid's Algorithm for Greatest Common Divisor (GCD) and Linear Search
 * with full decision tracing, input validation, and step-by-step state logging.
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>

class FlowchartSimulator {
public:
    // Flowchart-modeled Euclid's GCD Algorithm
    // Start -> Decision: b == 0? -> If Yes, Return a -> If No, a = b, b = a % b -> Loop
    static long long computeGCD(long long a, long long b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        std::cout << "\n[GCD Flowchart Simulation] Tracing gcd(" << a << ", " << b << "):\n";
        std::cout << std::setw(8) << "Step" << std::setw(12) << "State (a)" << std::setw(12) << "State (b)" << std::setw(20) << "Condition (b==0)" << "\n";
        std::cout << std::string(52, '-') << "\n";
        
        int step = 1;
        while (b != 0) {
            std::cout << std::setw(8) << step++ 
                      << std::setw(12) << a 
                      << std::setw(12) << b 
                      << std::setw(20) << "False (Continue)" << "\n";
            long long temp = b;
            b = a % b;
            a = temp;
        }
        std::cout << std::setw(8) << step 
                  << std::setw(12) << a 
                  << std::setw(12) << b 
                  << std::setw(20) << "True (Terminate)" << "\n";
        std::cout << "[Result] Final GCD = " << a << "\n";
        return a;
    }

    // Flowchart-modeled Linear Search with condition logging
    static int linearSearch(const std::vector<int>& arr, int key) {
        std::cout << "\n[Linear Search Simulation] Searching for key: " << key << "\n";
        std::cout << std::setw(8) << "Index" << std::setw(12) << "Value" << std::setw(20) << "Match Condition" << "\n";
        std::cout << std::string(40, '-') << "\n";
        
        for (size_t i = 0; i < arr.size(); ++i) {
            bool match = (arr[i] == key);
            std::cout << std::setw(8) << i 
                      << std::setw(12) << arr[i] 
                      << std::setw(20) << (match ? "MATCH FOUND!" : "No match") << "\n";
            if (match) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "  Unit 01 - Experiment 01: Pseudocode & Flowchart   \n";
    std::cout << "====================================================\n";

    try {
        // Test GCD Algorithm
        long long num1 = 1980, num2 = 168;
        std::cout << "Input Numbers: a = " << num1 << ", b = " << num2 << "\n";
        long long gcd = FlowchartSimulator::computeGCD(num1, num2);
        std::cout << "Verification: gcd(1980, 168) = " << gcd << " (Expected: 12)\n";

        // Test Linear Search Algorithm
        std::vector<int> data = {14, 29, 35, 42, 57, 63, 78, 89};
        std::cout << "\nInput Array: [";
        for (size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i] << (i + 1 < data.size() ? ", " : "");
        }
        std::cout << "]\n";

        int target = 57;
        int index = FlowchartSimulator::linearSearch(data, target);
        if (index != -1) {
            std::cout << "Element " << target << " found at index " << index << ".\n";
        } else {
            std::cout << "Element " << target << " not found in array.\n";
        }

        std::cout << "\nAll flowchart-modeled algorithms executed successfully.\n";
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
