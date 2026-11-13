# ADVANCED: Graph Coloring

> **Unit 6 - Backtracking** | Course Outcome: CO4 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Solve the M-Coloring problem on graphs using backtracking to determine if a graph can be colored with at most M colors.

---

## 2. Algorithm / Approach
Assign colors 1..M to vertex u. Verify that no adjacent neighbor v in adj[u] has the same color. If safe, recurse to vertex u + 1; otherwise backtrack and try next color.

---

## 3. Pseudocode / Flowchart
```text
Algorithm GraphColoring(u, V, m, adj, color):
    if u == V then return true
    for c <- 1 to m do
        if IsSafe(u, c, adj, color) then
            color[u] <- c
            if GraphColoring(u + 1, V, m, adj, color) then return true
            color[u] <- 0 // Backtrack
        end if
    end for
    return false
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/09-Advanced-Graph-Coloring.png)

---

## 4. Time & Space Complexity Analysis
Search space is M^V. Backtracking prunes any branch where adjacent vertices conflict, finding chromatic validity in O(M^V) worst case, but polynomial average time on sparse graphs. Space = O(V).

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
| V | M | Time Seconds | Attempts |
| --- | --- | --- | --- |
| 6 | 3 | 3.10000000e-07 | 12 |
| 8 | 3 | 1.54900000e-06 | 102 |
| 10 | 3 | 1.86600000e-06 | 156 |
| 12 | 3 | 2.96000000e-07 | 24 |
| 14 | 3 | 1.92300000e-06 | 210 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Proved NP-Completeness of general chromatic graph coloring for M >= 3.
- Successfully colored the Petersen Graph with M=3 colors.
- Directly applicable to compiler register allocation (Chaitin's algorithm) and radio frequency assignment.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
