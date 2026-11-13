# 0/1 Knapsack: DP vs Branch and Bound

> **Unit 7 - NP-Hard, NP-Complete & Advanced Optimization** | Course Outcome: CO5, CO7 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Comprehensive comparison of Dynamic Programming vs Branch and Bound on 0/1 Knapsack across varying capacities and items.

---

## 2. Algorithm / Approach
Benchmark DP (pseudo-polynomial O(n*W) table evaluation) against Branch and Bound (fractional upper bound tree pruning) on identical instances.

---

## 3. Pseudocode / Flowchart
```text
Compare: DP Time = O(n * W) vs Branch & Bound Time = Pruned Tree search.
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/04-Knapsack-DP-vs-Branch-and-Bound.png)

---

## 4. Time & Space Complexity Analysis
When W is small, DP table is fast and predictable. When W is very large (e.g. W = 10^9), DP table allocation fails (O(n*W) memory), whereas Branch and Bound operates independently of W magnitude, relying only on item count and bound tightness.

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
| 10 | 2.61500000e-06 | 0.016 | 0.003 | 18 |
| 15 | 2.36200000e-06 | 0.026 | 0.002 | 28 |
| 20 | 3.51200000e-06 | 0.035 | 0.004 | 38 |
| 25 | 4.11000000e-06 | 0.054 | 0.004 | 48 |
| 28 | 4.51700000e-06 | 0.064 | 0.005 | 54 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Identified precise problem characteristics dictating choice of DP vs Branch & Bound.
- Learned that Branch & Bound is immune to large capacity values that break DP table allocations.
- Essential for enterprise resource management and optimization software architecture.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
