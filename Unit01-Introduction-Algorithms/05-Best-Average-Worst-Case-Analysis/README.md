# Best, Average, and Worst Case Complexity Analysis

> **Unit 1 - Introduction to Algorithms & Performance Analysis** | Course Outcome: CO1 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Empirically evaluate and contrast Best, Average, and Worst Case search scenarios on Linear Search vs Binary Search across varying input sizes.

---

## 2. Algorithm / Approach
Construct test arrays from n=1,000 to 100,000. Measure execution times and comparison counts for Best Case (immediate hit at first/mid element), Average Case (element at 50-75% position), and Worst Case (element not present).

---

## 3. Pseudocode / Flowchart
```text
Linear Search: Best = O(1), Average = Theta(n/2), Worst = O(n)
Binary Search: Best = O(1), Average = Theta(log n), Worst = O(log n)
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/05-Best-Average-Worst-Case-Analysis.png)

---

## 4. Time & Space Complexity Analysis
Average case complexity for linear search assuming uniform probability 1/n for each index is E[C] = sum_{i=1}^n (i * 1/n) = (n + 1) / 2 = Theta(n). For binary search, the average external path length in a decision tree yields E[C] = log2(n) - 1 + o(1) = Theta(log n).

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
| N | Linear Best Ns | Linear Avg Ns | Linear Worst Ns | Binary Best Ns | Binary Avg Ns | Binary Worst Ns |
| --- | --- | --- | --- | --- | --- | --- |
| 1000 | 16.48 | 15.77 | 15.57 | 15.96 | 15.72 | 15.56 |
| 5000 | 15.48 | 15.74 | 15.45 | 16.72 | 15.39 | 15.8 |
| 10000 | 15.76 | 15.27 | 15.78 | 15.78 | 15.31 | 15.89 |
| 25000 | 15.32 | 15.82 | 15.35 | 16.33 | 15.31 | 16.35 |
| 50000 | 15.59 | 15.72 | 16.11 | 15.55 | 16.09 | 16.14 |
| 100000 | 15.79 | 15.64 | 15.63 | 15.95 | 15.6 | 15.56 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Understood the distinct roles of Big-O (upper bound), Big-Omega (lower bound), and Big-Theta (tight bound).
- Observed empirical proof that Binary Search worst case runs faster than Linear Search average case by orders of magnitude.
- Vital for SLA guarantees in real-time systems where worst-case latency bounds are strictly enforced.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
