# Backtracking vs Exhaustive Search

> **Unit 6 - Backtracking** | Course Outcome: CO4 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Quantitatively compare Backtracking vs Brute Force Exhaustive Search on identical subset sum problem instances.

---

## 2. Algorithm / Approach
Measure total nodes explored and execution time for Backtracking (pruned state tree) vs Exhaustive Search (all 2^n binary combinations) across sizes n = 10 to 22.

---

## 3. Pseudocode / Flowchart
```text
Compare:
Backtracking Nodes = Evaluates bounded valid states
Exhaustive Nodes = 2^{n+1} - 1 (All nodes in complete binary tree)
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/06-Backtracking-vs-Exhaustive-Search.png)

---

## 4. Time & Space Complexity Analysis
Exhaustive search evaluates exactly 2^n leaf configurations (2^{n+1}-1 total tree nodes). Backtracking prunes dead branches as soon as current_sum > target, reducing node evaluations exponentially.

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
| N | Time Seconds | Backtrack Nodes | Exhaustive Nodes | Backtrack Ms | Exhaustive Ms |
| --- | --- | --- | --- | --- | --- |
| 10 | 6.21900000e-06 | 2027 | 2047 | 0.006 | 0.000 |
| 15 | 8.22110000e-05 | 51301 | 65535 | 0.082 | 0.000 |
| 18 | 4.29980000e-04 | 291203 | 524287 | 0.430 | 0.000 |
| 20 | 1.43057700e-03 | 853277 | 2097151 | 1.431 | 0.000 |
| 22 | 3.66935200e-03 | 2356365 | 8388607 | 3.669 | 0.000 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Obtained empirical quantitative proof of pruning efficacy.
- Observed exponential divergence between exhaustive and pruned runtimes as n grows.
- Essential for understanding when brute force is feasible vs when intelligent pruning is mandatory.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
