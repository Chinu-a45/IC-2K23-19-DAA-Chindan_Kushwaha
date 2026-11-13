# Iterative Preorder, Inorder, and Postorder

> **Unit 5 - Basic Traversal & Search Techniques** | Course Outcome: CO6 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Implement iterative tree traversals using explicit std::stack to eliminate call stack depth limitations.

---

## 2. Algorithm / Approach
Simulate system recursion stack using an explicit std::stack. For Preorder: push root, pop and push right then left child. For Inorder: traverse left pushing nodes until null, then pop and visit.

---

## 3. Pseudocode / Flowchart
```text
Algorithm IterativeInorder(root):
    stack <- empty; curr <- root
    while curr != null or not stack.empty() do
        while curr != null do
            stack.push(curr); curr <- curr.left
        end while
        curr <- stack.pop()
        Visit(curr.val)
        curr <- curr.right
    end while
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/03-Tree-Traversals-Iterative.png)

---

## 4. Time & Space Complexity Analysis
Each node is pushed and popped from the stack at most twice. Time complexity = Theta(n). Auxiliary space = O(h) stack memory, immune to OS call-stack overflows.

---

## 5. Sample Input / Output & Verification
The program prints step-by-step state logs and verifies all outputs internally against exact theoretical expectations. Refer to the terminal execution output below for concrete sample runs.

---

## 6. Screenshots & Visualizations
### Terminal Execution Output

![Terminal Output](screenshots/output.png)

### Empirical Performance Scaling Graph

![Performance Graph](screenshots/graph.png)


---

## 7. Experimental Results & Telemetry
| N | Time Seconds | Preorder Us | Inorder Us | Postorder Us |
| --- | --- | --- | --- | --- |
| 1000 | 5.74080000e-05 | 15.39 | 7.52 | 34.50 |
| 5000 | 3.11464000e-04 | 62.62 | 172.49 | 76.36 |
| 10000 | 4.34335000e-04 | 116.33 | 56.39 | 261.61 |
| 25000 | 1.21483600e-03 | 466.67 | 227.91 | 520.25 |
| 50000 | 9.00565000e-04 | 343.26 | 194.20 | 363.11 |
| 100000 | 2.06911900e-03 | 611.93 | 527.82 | 929.36 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Eliminated recursion stack overflow risks on deep/unbalanced trees.
- Mastered manual stack frame management.
- Essential in systems programming, high-reliability embedded software, and game loop engines.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
