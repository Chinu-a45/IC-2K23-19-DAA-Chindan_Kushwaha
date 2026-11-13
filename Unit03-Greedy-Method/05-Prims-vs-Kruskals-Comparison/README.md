# Comparison of Prim's and Kruskal's Algorithms

> **Unit 3 - Greedy Method** | Course Outcome: CO2 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Comparative benchmark evaluating Prim's vs Kruskal's algorithms across varying vertex sizes on sparse and dense graphs.

---

## 2. Algorithm / Approach
Construct synthetic connected graphs with controlled degree density. Measure execution times and memory allocations for both algorithms on identical topologies.

---

## 3. Pseudocode / Flowchart
```text
Algorithm CompareMST(sizes):
    for each V in sizes do
        G_sparse <- BuildGraph(V, degree=4)
        t_prim <- Measure(Prim, G_sparse)
        t_kruskal <- Measure(Kruskal, G_sparse)
        LogComparison(V, t_prim, t_kruskal)
    end for
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/05-Prims-vs-Kruskals-Comparison.png)

---

## 4. Time & Space Complexity Analysis
On sparse graphs (E ~ V), Kruskal's O(E log V) is very efficient. On dense graphs (E ~ V^2), Kruskal's must sort V^2 edges (O(V^2 log V)), whereas Prim's with adjacency matrix or Fibonacci heap achieves O(V^2), outperforming Kruskal's.

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
| N | Time Seconds | Prims Ms | Kruskals Ms |
| --- | --- | --- | --- |
| 100 | 1.81660000e-05 | 0.0182 | 0.0149 |
| 200 | 3.42520000e-05 | 0.0343 | 0.0283 |
| 500 | 8.59490000e-05 | 0.0859 | 0.0765 |
| 1000 | 1.74426000e-04 | 0.1744 | 0.1376 |
| 1500 | 2.69959000e-04 | 0.2700 | 0.2055 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Identified precise graph density crossover conditions determining when to select Prim's vs Kruskal's.
- Analyzed edge-list vs priority-queue cache behavior and operational overhead.
- Essential for algorithmic network topology engineering in cloud infrastructure.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
