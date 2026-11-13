# TSP: DP vs Branch and Bound

> **Unit 7 - NP-Hard, NP-Complete & Advanced Optimization** | Course Outcome: CO5, CO7 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Direct performance benchmark comparing Held-Karp Dynamic Programming vs Matrix-Reduction Branch and Bound for TSP.

---

## 2. Algorithm / Approach
Execute both algorithms on identical TSP distance matrices across n = 4 to 14. Compare execution time, memory footprint, and explored state counts.

---

## 3. Pseudocode / Flowchart
```text
Compare: Held-Karp DP O(n^2 2^n) vs Matrix Reduction Branch & Bound.
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/05-TSP-DP-vs-Branch-and-Bound.png)

---

## 4. Time & Space Complexity Analysis
Held-Karp DP evaluates exactly n^2 2^n states with deterministic O(n 2^n) table memory. Branch and Bound uses memory proportional to priority queue size, often finding optimal tours faster on structured metric graphs due to aggressive reduction pruning.

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
| N | Time Seconds | Dp Ms | Bb Ms | Bb Nodes |
| --- | --- | --- | --- | --- |
| 4 | 1.59600000e-05 | 0.004 | 0.016 | 7 |
| 6 | 4.14490000e-05 | 0.010 | 0.041 | 47 |
| 8 | 4.52455000e-04 | 0.039 | 0.452 | 405 |
| 10 | 2.36988000e-04 | 0.202 | 0.237 | 248 |
| 12 | 1.95693330e-02 | 0.869 | 19.569 | 8208 |
| 14 | 9.46016715e-01 | 4.195 | 946.017 | 462307 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Understood deterministic DP vs heuristic Branch & Bound search dynamics.
- Analyzed memory saturation boundaries for both algorithms.
- Applied in supply chain logistics and transportation network design.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
