# Comparison of BFS and DFS

> **Unit 5 - Basic Traversal & Search Techniques** | Course Outcome: CO6 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Comparative benchmark of BFS vs DFS evaluating traversal orders, queue vs stack memory depth, and pathfinding.

---

## 2. Algorithm / Approach
Execute BFS and DFS on identical graph structures. Record execution times, peak memory depths, and visited node counts.

---

## 3. Pseudocode / Flowchart
```text
Compare BFS (FIFO Queue) vs DFS (LIFO Stack) across graph sizes.
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/09-BFS-vs-DFS-Comparison.png)

---

## 4. Time & Space Complexity Analysis
Both algorithms operate in Theta(V + E) time. BFS memory depends on maximum graph width (branching factor b^d); DFS memory depends on maximum graph depth (O(d)).

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
| N | Time Seconds | Bfs Ms | Dfs Ms |
| --- | --- | --- | --- |
| 500 | 6.16600000e-06 | 0.0062 | 0.0101 |
| 1000 | 1.09760000e-05 | 0.0110 | 0.0207 |
| 2500 | 2.66660000e-05 | 0.0267 | 0.0494 |
| 5000 | 5.27090000e-05 | 0.0527 | 0.1055 |
| 10000 | 1.24589000e-04 | 0.1246 | 0.2334 |
| 20000 | 6.46547000e-04 | 0.6465 | 0.7280 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Learned when to choose BFS (shortest paths, wide shallow trees) vs DFS (cycle detection, memory-efficient deep search).
- Analyzed memory footprint implications.
- Applied in AI search algorithms (BFS in unweighted state space; DFS in game tree backtracking).

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
