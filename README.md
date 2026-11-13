# RollNo-DAA-Your_Name

**IC-709 B | Design & Analysis of Algorithms Laboratory**  
*Master of Computer Applications (MCA) — International Institute of Professional Studies (IIPS), Devi Ahilya Vishwavidyalaya, Indore (DAVV)*

---

## Laboratory Overview
This repository contains the complete, production-grade implementation of all **55 laboratory experiments** prescribed in the **IC-709 B Design & Analysis of Algorithms Laboratory** syllabus. Every program is written in **modern C++ (C++17)**, featuring modular architectures, strict input validation, defensive boundary verification, empirical telemetry logging (`results.csv`), and high-resolution wall-clock/CPU timing via `std::chrono`.

All experiments include:
- Standalone C++ source code (`main.cpp`)
- Step-by-step console state logging and automated correctness verification
- Empirical telemetry dataset (`results.csv`)
- High-resolution terminal output screenshots (`screenshots/output.png`)
- Empirical runtime vs. theoretical complexity scaling graphs (`screenshots/graph.png`)
- Algorithmic flowcharts (`docs/algorithm-flowcharts/*.png`)
- Comprehensive mathematical derivations and recurrence relations

---

## Repository Structure

```text
├── Unit01-Introduction-Algorithms/       # Unit 1: Introduction & Performance Analysis (CO1) [7 Experiments]
├── Unit02-Divide-and-Conquer/            # Unit 2: Divide and Conquer Paradigm (CO1) [7 Experiments]
├── Unit03-Greedy-Method/                 # Unit 3: Greedy Method Optimization (CO2) [6 Experiments]
├── Unit04-Dynamic-Programming/           # Unit 4: Dynamic Programming (CO3) [9 Experiments]
├── Unit05-Traversal-and-Search/          # Unit 5: Basic Traversal & Search Techniques (CO6) [11 Experiments]
├── Unit06-Backtracking/                  # Unit 6: Backtracking & CSP (CO4) [9 Experiments]
├── Unit07-NP-Hard-NP-Complete/           # Unit 7: NP-Hard & Advanced Optimization (CO5, CO7) [6 Experiments]
│
├── docs/                                 # Formal Laboratory Documentation & Reports
│   ├── algorithm-flowcharts/             # 55 flowcharts (PNG) for each experiment
│   ├── algorithm-pseudocode/             # Horowitz & Sahni / CLRS style pseudocode reference
│   ├── complexity-analysis/              # Mathematical derivations & Master Theorem analysis
│   ├── diagrams/                         # Recursion trees, state-space trees, PlantUML & Draw.io
│   ├── performance-analysis.pdf          # Full publication-quality multi-page performance report
│   └── final-report.pdf                  # Complete laboratory manual and final submission report
│
├── run_all.sh                            # One-step automated compilation and verification runner
├── Makefile                              # Make build automation
├── .gitignore                            # Clean binary and editor exclusions
└── README.md                             # Repository overview and master index
```

---

## Detailed Unit & Experiment Inventory

### [Unit 01: Introduction to Algorithms & Performance Analysis](Unit01-Introduction-Algorithms/) (CO1)
1. **[01-Pseudocode-Flowchart](Unit01-Introduction-Algorithms/01-Pseudocode-Flowchart/)**: Algorithm Using Pseudocode and Flowchart (Euclid's GCD & Linear Search)
2. **[02-Array-Operations](Unit01-Introduction-Algorithms/02-Array-Operations/)**: Basic Operations on Arrays (Insert, Delete, Traverse, Update, Search)
3. **[03-Binary-Search-Iterative](Unit01-Introduction-Algorithms/03-Binary-Search-Iterative/)**: Iterative Binary Search with loop invariants & comparison counting
4. **[04-Binary-Search-Recursive](Unit01-Introduction-Algorithms/04-Binary-Search-Recursive/)**: Recursive Binary Search using recurrence $T(n) = T(n/2) + O(1)$
5. **[05-Best-Average-Worst-Case-Analysis](Unit01-Introduction-Algorithms/05-Best-Average-Worst-Case-Analysis/)**: Best, Average, and Worst Case Complexity evaluation
6. **[06-Execution-Time-Measurement](Unit01-Introduction-Algorithms/06-Execution-Time-Measurement/)**: High-resolution execution time measurement across varying input sizes
7. **[07-Algorithm-Performance-Analyzer](Unit01-Introduction-Algorithms/07-Algorithm-Performance-Analyzer/)**: **APPLICATION:** Algorithm Performance Analyzer comparing theoretical and empirical scaling

### [Unit 02: Divide and Conquer](Unit02-Divide-and-Conquer/) (CO1)
1. **[01-Binary-Search-DC](Unit02-Divide-and-Conquer/01-Binary-Search-DC/)**: Binary Search (Divide and Conquer formulation)
2. **[02-Max-Min](Unit02-Divide-and-Conquer/02-Max-Min/)**: Maximum and Minimum using D&C (reducing comparisons to $3n/2 - 2$)
3. **[03-Merge-Sort](Unit02-Divide-and-Conquer/03-Merge-Sort/)**: Stable Merge Sort ($O(n \log n)$ invariant runtime)
4. **[04-Quick-Sort](Unit02-Divide-and-Conquer/04-Quick-Sort/)**: Quick Sort with median-of-three pivot partitioning
5. **[05-Heap-Sort](Unit02-Divide-and-Conquer/05-Heap-Sort/)**: In-place Heap Sort ($O(n)$ build heap, $O(1)$ space)
6. **[06-Strassen-Matrix-Multiplication](Unit02-Divide-and-Conquer/06-Strassen-Matrix-Multiplication/)**: Strassen's Matrix Multiplication ($O(n^{2.807})$ sub-cubic complexity)
7. **[07-Sorting-Performance-Comparison-System](Unit02-Divide-and-Conquer/07-Sorting-Performance-Comparison-System/)**: **APPLICATION:** Sorting Performance Comparison System (Merge vs Quick vs Heap)

### [Unit 03: Greedy Method](Unit03-Greedy-Method/) (CO2)
1. **[01-Fractional-Knapsack](Unit03-Greedy-Method/01-Fractional-Knapsack/)**: Fractional Knapsack using profit/weight ratio greedy choice
2. **[02-Job-Sequencing-with-Deadlines](Unit03-Greedy-Method/02-Job-Sequencing-with-Deadlines/)**: Job Sequencing with Deadlines maximizing revenue
3. **[03-Prims-Algorithm](Unit03-Greedy-Method/03-Prims-Algorithm/)**: Minimum Cost Spanning Tree via Prim's Algorithm (Priority Queue)
4. **[04-Kruskals-Algorithm](Unit03-Greedy-Method/04-Kruskals-Algorithm/)**: Minimum Cost Spanning Tree via Kruskal's Algorithm (DSU with union by rank and path compression)
5. **[05-Prims-vs-Kruskals-Comparison](Unit03-Greedy-Method/05-Prims-vs-Kruskals-Comparison/)**: Comparative benchmark of Prim's vs Kruskal's on Sparse vs Dense graphs
6. **[06-Minimum-Cost-Network-Design-System](Unit03-Greedy-Method/06-Minimum-Cost-Network-Design-System/)**: **APPLICATION:** Minimum-Cost Network Design System for fiber-optic backbone

### [Unit 04: Dynamic Programming](Unit04-Dynamic-Programming/) (CO3)
1. **[01-Fibonacci-Recursion](Unit04-Dynamic-Programming/01-Fibonacci-Recursion/)**: Fibonacci using Recursion demonstrating exponential $O(2^n)$ call explosion
2. **[02-Fibonacci-Memoization](Unit04-Dynamic-Programming/02-Fibonacci-Memoization/)**: Fibonacci using Top-down Memoization ($O(n)$) and Space-Optimized Tabulation ($O(1)$)
3. **[03-Knapsack-01-DP](Unit04-Dynamic-Programming/03-Knapsack-01-DP/)**: 0/1 Knapsack using DP table with full backtracking item reconstruction
4. **[04-Multistage-Graph](Unit04-Dynamic-Programming/04-Multistage-Graph/)**: Shortest path in Multistage Graph via backward dynamic programming formulation
5. **[05-Floyd-Warshall](Unit04-Dynamic-Programming/05-Floyd-Warshall/)**: All-Pairs Shortest Path (Floyd-Warshall $O(V^3)$ algorithm)
6. **[06-Single-Source-Shortest-Path](Unit04-Dynamic-Programming/06-Single-Source-Shortest-Path/)**: Bellman-Ford DP handling negative weights and cycle detection
7. **[07-TSP-DP](Unit04-Dynamic-Programming/07-TSP-DP/)**: Traveling Salesperson Problem using Held-Karp bitmask DP ($O(n^2 2^n)$)
8. **[08-Greedy-vs-DP-Comparison](Unit04-Dynamic-Programming/08-Greedy-vs-DP-Comparison/)**: Rigorous proof of Greedy failure on discrete items vs DP global optimality
9. **[09-Route-Optimization-System](Unit04-Dynamic-Programming/09-Route-Optimization-System/)**: **APPLICATION:** Route Optimization System combining Floyd-Warshall and TSP-DP

### [Unit 05: Basic Traversal & Search Techniques](Unit05-Traversal-and-Search/) (CO6)
1. **[01-Binary-Tree-Creation](Unit05-Traversal-and-Search/01-Binary-Tree-Creation/)**: Binary Search Tree creation, node insertion, search, and height calculation
2. **[02-Tree-Traversals-Recursive](Unit05-Traversal-and-Search/02-Tree-Traversals-Recursive/)**: Recursive Preorder, Inorder, and Postorder traversals
3. **[03-Tree-Traversals-Iterative](Unit05-Traversal-and-Search/03-Tree-Traversals-Iterative/)**: Iterative tree traversals using explicit `std::stack`
4. **[04-Graph-Adjacency-Matrix](Unit05-Traversal-and-Search/04-Graph-Adjacency-Matrix/)**: Graph representation using 2D Adjacency Matrix ($O(V^2)$ space)
5. **[05-Graph-Adjacency-List](Unit05-Traversal-and-Search/05-Graph-Adjacency-List/)**: Graph representation using Adjacency List ($O(V + E)$ space)
6. **[06-BFS](Unit05-Traversal-and-Search/06-BFS/)**: Breadth First Search using `std::queue` with unweighted shortest hop calculation
7. **[07-DFS-Recursive](Unit05-Traversal-and-Search/07-DFS-Recursive/)**: Recursive Depth First Search for cycle and component discovery
8. **[08-DFS-Iterative](Unit05-Traversal-and-Search/08-DFS-Iterative/)**: Iterative Depth First Search using explicit `std::stack`
9. **[09-BFS-vs-DFS-Comparison](Unit05-Traversal-and-Search/09-BFS-vs-DFS-Comparison/)**: Comparative benchmark of BFS vs DFS on traversal orders and memory depth
10. **[10-Matrix-vs-List-Comparison](Unit05-Traversal-and-Search/10-Matrix-vs-List-Comparison/)**: Adjacency Matrix vs Adjacency List memory footprint and scanning benchmark
11. **[11-Graph-Exploration-System](Unit05-Traversal-and-Search/11-Graph-Exploration-System/)**: **APPLICATION:** Network Topology Explorer with cycle detection and articulation cut-vertices

### [Unit 06: Backtracking](Unit06-Backtracking/) (CO4)
1. **[01-General-Backtracking-Method](Unit06-Backtracking/01-General-Backtracking-Method/)**: General Backtracking framework with explicit bounding functions
2. **[02-4-Queens](Unit06-Backtracking/02-4-Queens/)**: 4-Queens problem with full state-space exploration and rollback logging
3. **[03-8-Queens](Unit06-Backtracking/03-8-Queens/)**: 8-Queens problem discovering all 92 distinct solutions
4. **[04-N-Queens](Unit06-Backtracking/04-N-Queens/)**: Generalized N-Queens solver evaluating scalability from $N = 4$ to $12$
5. **[05-Sum-of-Subsets](Unit06-Backtracking/05-Sum-of-Subsets/)**: Sum of Subsets with double-bounding lookahead pruning
6. **[06-Backtracking-vs-Exhaustive-Search](Unit06-Backtracking/06-Backtracking-vs-Exhaustive-Search/)**: Empirical node count and time comparison of Backtracking vs Brute Force ($2^n$)
7. **[07-Constraint-Satisfaction-Solver](Unit06-Backtracking/07-Constraint-Satisfaction-Solver/)**: **APPLICATION:** General CSP Map Coloring solver with MRV and Forward Checking
8. **[08-Advanced-Sudoku-Solver](Unit06-Backtracking/08-Advanced-Sudoku-Solver/)**: **ADVANCED:** 9x9 Sudoku solver using backtracking with row/col/box constraint propagation
9. **[09-Advanced-Graph-Coloring](Unit06-Backtracking/09-Advanced-Graph-Coloring/)**: **ADVANCED:** M-Coloring problem on graphs (Petersen Graph 3-coloring verification)

### [Unit 07: NP-Hard, NP-Complete & Advanced Optimization](Unit07-NP-Hard-NP-Complete/) (CO5, CO7)
1. **[01-Exhaustive-Search-Demo](Unit07-NP-Hard-NP-Complete/01-Exhaustive-Search-Demo/)**: Exhaustive Search Demonstration illustrating combinatorial explosion on Knapsack and TSP
2. **[02-Knapsack-Branch-and-Bound](Unit07-NP-Hard-NP-Complete/02-Knapsack-Branch-and-Bound/)**: 0/1 Knapsack using Least-Cost (LC) Branch and Bound with Fractional relaxation upper bounds
3. **[03-TSP-Branch-and-Bound](Unit07-NP-Hard-NP-Complete/03-TSP-Branch-and-Bound/)**: TSP using Branch and Bound with Reduced Cost Matrix lower bounding
4. **[04-Knapsack-DP-vs-Branch-and-Bound](Unit07-NP-Hard-NP-Complete/04-Knapsack-DP-vs-Branch-and-Bound/)**: Comparative benchmark of 0/1 Knapsack: Dynamic Programming vs Branch and Bound
5. **[05-TSP-DP-vs-Branch-and-Bound](Unit07-NP-Hard-NP-Complete/05-TSP-DP-vs-Branch-and-Bound/)**: Comparative benchmark of TSP: Held-Karp DP vs Branch and Bound
6. **[06-Optimization-Algorithm-Comparison-System](Unit07-NP-Hard-NP-Complete/06-Optimization-Algorithm-Comparison-System/)**: **APPLICATION:** Unified Optimization Comparison System (Exhaustive vs DP vs Branch & Bound)

---

## How to Build and Run

### Prerequisites
A modern C++ compiler supporting C++17:
```bash
sudo apt update && sudo apt install -y g++ make
```

### 1. Run the Automated Test Suite (All 55 Experiments)
Execute the complete test suite with a single command:
```bash
./run_all.sh
```
Or via Makefile:
```bash
make
```

### 2. Compile and Run an Individual Experiment
Navigate to any experiment directory and compile with `g++`:
```bash
cd Unit02-Divide-and-Conquer/03-Merge-Sort
g++ -std=c++17 -O2 main.cpp -o main
./main
```

---

## Laboratory Documentation Artifacts
The `docs/` folder contains complete publication-quality documentation:
- **[docs/performance-analysis.pdf](docs/performance-analysis.pdf)**: Comprehensive 4-page performance report with empirical tables, memory footprint analyses, and speedup graphs.
- **[docs/final-report.pdf](docs/final-report.pdf)**: Complete 5-page formal lab manual report containing institutional declarations, syllabus mapping, unit summaries, and evaluation sign-offs.
- **[docs/algorithm-flowcharts/](docs/algorithm-flowcharts/)**: High-resolution flowchart PNG images for all 55 experiments.
- **[docs/algorithm-pseudocode/](docs/algorithm-pseudocode/)**: Formal Horowitz & Sahni / CLRS style pseudocode specifications.
- **[docs/complexity-analysis/](docs/complexity-analysis/)**: Master Theorem applications, recurrence derivations, and complexity summary tables.
- **[docs/diagrams/](docs/diagrams/)**: Architecture overviews, recursion trees, state-space trees, and UML/Draw.io sources.

---

## Progress Tracker
- [x] Unit01-Introduction-Algorithms (7/7 Experiments Complete)
- [x] Unit02-Divide-and-Conquer (7/7 Experiments Complete)
- [x] Unit03-Greedy-Method (6/6 Experiments Complete)
- [x] Unit04-Dynamic-Programming (9/9 Experiments Complete)
- [x] Unit05-Traversal-and-Search (11/11 Experiments Complete)
- [x] Unit06-Backtracking (9/9 Experiments Complete)
- [x] Unit07-NP-Hard-NP-Complete (6/6 Experiments Complete)
- [x] Documentation & Publication PDFs (`final-report.pdf`, `performance-analysis.pdf`)
- [x] All 55 Flowcharts & Performance Visualizations
- [x] Zero placeholders — 100% ready for repository commit
