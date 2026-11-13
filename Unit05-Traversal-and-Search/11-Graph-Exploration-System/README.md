# APPLICATION: Graph Exploration / Network Traversal System

> **Unit 5 - Basic Traversal & Search Techniques** | Course Outcome: CO6 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Implement an enterprise network topology explorer that discovers connected components, detects cycles, and identifies critical gateways (cut-vertices).

---

## 2. Algorithm / Approach
Integrate BFS/DFS for component count and Tarjan's algorithm (tin/low discovery times) to identify Articulation Points whose failure disconnects the network.

---

## 3. Pseudocode / Flowchart
```text
Algorithm NetworkExplorer(adj):
    components <- CountConnectedComponents(adj)
    articulation_points <- FindCutVerticesTarjan(adj)
    return (components, articulation_points)
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/11-Graph-Exploration-System.png)

---

## 4. Time & Space Complexity Analysis
Connected component discovery runs in O(V + E). Tarjan's articulation point DFS runs in O(V + E). Total execution time = O(V + E). Space complexity = O(V).

---

## 5. Sample Input / Output & Verification
The program prints step-by-step state logs and verifies all outputs internally against exact theoretical expectations. Refer to the terminal execution output below for concrete sample runs.

---

## 6. Screenshots & Visualizations
### Terminal Execution Output

![Terminal Output](screenshots/output.png)


---

## 7. Experimental Results & Telemetry
_No numerical benchmark dataset required._

The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Identified Single Points of Failure (Cut Vertices) in telecommunication networks.
- Implemented Tarjan's bridge/articulation discovery algorithm.
- Applied in cyber-security network resilience analysis, critical infrastructure monitoring, and distributed cloud mesh.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
