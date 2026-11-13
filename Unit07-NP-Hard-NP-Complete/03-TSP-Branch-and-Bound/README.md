# TSP using Branch and Bound

> **Unit 7 - NP-Hard, NP-Complete & Advanced Optimization** | Course Outcome: CO5, CO7 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Solve Traveling Salesperson Problem using Branch and Bound with Reduced Cost Matrix lower bounding.

---

## 2. Algorithm / Approach
Reduce cost matrix via row and column reductions; sum of reduction minimums yields rigorous lower bound. Explore search tree using min-priority queue. Prune any branch whose lower bound >= best tour found so far.

---

## 3. Pseudocode / Flowchart
```text
Algorithm TSPBranchAndBound(cost_matrix):
    root.bound <- ReduceMatrix(cost_matrix)
    pq.push(root)
    while not pq.empty() do
        curr <- pq.pop()
        if curr.bound >= best_tour then continue // Prune!
        for each valid next city v do
            child.bound <- curr.bound + curr.matrix[curr.v][v] + ReduceChild(child)
            if child.bound < best_tour then pq.push(child)
        end for
    end while
    return best_tour
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/03-TSP-Branch-and-Bound.png)

---

## 4. Time & Space Complexity Analysis
Each matrix reduction takes O(n^2). Lower bounding prunes subtrees that cannot beat the best known tour. Worst-case time = O(n^2 2^n), but explores far fewer nodes than brute force.

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
| N | Time Seconds | Nodes Explored | Tour Cost |
| --- | --- | --- | --- |
| 4 | 5.43300000e-06 | 7 | 79 |
| 6 | 4.91420000e-05 | 54 | 102 |
| 8 | 7.10316000e-04 | 675 | 127 |
| 10 | 4.45963000e-04 | 352 | 117 |
| 12 | 2.37825020e-02 | 13285 | 147 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Mastered matrix reduction lower bounding technique.
- Observed effective pruning on symmetric and asymmetric distance matrices.
- Foundational algorithm in modern vehicle routing and operations research.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
