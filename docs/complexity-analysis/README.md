# Comprehensive Complexity Analysis & Recurrence Relations

This document details the mathematical derivation of time and space complexities, Master Theorem applications, and empirical verification for all algorithms across Units 1 to 7.

---

## 1. Master Theorem for Divide-and-Conquer Recurrences

For recurrences of the form:
$$T(n) = a T(n/b) + f(n)$$
where $a \ge 1, b > 1$:

Let $c_{crit} = \log_b a$:
1. **Case 1**: If $f(n) = O(n^c)$ where $c < \log_b a$, then $T(n) = \Theta(n^{\log_b a})$.
2. **Case 2**: If $f(n) = \Theta(n^{\log_b a} \log^k n)$ where $k \ge 0$, then $T(n) = \Theta(n^{\log_b a} \log^{k+1} n)$.
3. **Case 3**: If $f(n) = \Omega(n^c)$ where $c > \log_b a$ and regularity condition holds, then $T(n) = \Theta(f(n))$.

---

## 2. Derivation of Specific Recurrence Relations

### Binary Search (Divide and Conquer)
- **Recurrence**: $T(n) = T(n/2) + \Theta(1)$
- **Master Theorem Parameters**: $a = 1, b = 2, f(n) = \Theta(1) = \Theta(n^0)$
- $\log_b a = \log_2 1 = 0$
- Falls into **Case 2** ($k=0$):
  $$T(n) = \Theta(n^0 \log^1 n) = \Theta(\log n)$$
- **Space Complexity**: Iterative is $O(1)$, Recursive is $O(\log n)$ call stack frames.

### Maximum & Minimum (Divide and Conquer)
- **Recurrence for number of comparisons**:
  $$C(n) = 2 C(n/2) + 2$$
  with base cases $C(1) = 0, C(2) = 1$.
- **Solution via expansion**:
  $$C(n) = 2 \left(2 C(n/4) + 2\right) + 2 = 4 C(n/4) + 4 + 2 = 2^k C(n/2^k) + \sum_{i=1}^{k} 2^i$$
  For $n = 2^k$:
  $$C(n) = n \cdot C(1) + 2(2^k - 1) = \frac{3n}{2} - 2$$
- **Comparison saving**: Compared to standard sequential search requiring $2n - 2$ comparisons, D&C achieves $1.5n - 2$ comparisons (25% reduction).

### Merge Sort
- **Recurrence**: $T(n) = 2 T(n/2) + \Theta(n)$
- **Master Theorem Parameters**: $a = 2, b = 2, f(n) = \Theta(n)$
- $\log_b a = \log_2 2 = 1$
- Falls into **Case 2** ($k=0$):
  $$T(n) = \Theta(n \log n)$$
- **Space Complexity**: $\Theta(n)$ auxiliary array for merge buffer.

### Quick Sort
- **Best / Average Case Recurrence**: $T(n) = 2 T(n/2) + \Theta(n) \implies O(n \log n)$
- **Worst Case Recurrence** (unbalanced partition):
  $$T(n) = T(n-1) + T(0) + \Theta(n) \implies T(n) = \sum_{i=1}^n i = \Theta(n^2)$$
- **Auxiliary Space**: $O(\log n)$ average recursion stack depth (with tail call optimization / balanced pivot).

### Strassen's Matrix Multiplication
- **Recurrence**: $T(n) = 7 T(n/2) + \Theta(n^2)$
- **Master Theorem Parameters**: $a = 7, b = 2, f(n) = \Theta(n^2)$
- $\log_b a = \log_2 7 \approx 2.80735$
- Since $f(n) = O(n^2)$ and $2 < 2.807$, falls into **Case 1**:
  $$T(n) = \Theta\left(n^{\log_2 7}\right) \approx \Theta(n^{2.807})$$
- Substantial speedup over naive cubic $O(n^3)$ matrix multiplication.

---

## 3. Master Complexity Summary Table

| Unit | Algorithm | Best Case Time | Average Case Time | Worst Case Time | Space Complexity | Paradigm |
|---|---|---|---|---|---|---|
| **01** | Linear Search | $O(1)$ | $O(n)$ | $O(n)$ | $O(1)$ | Brute Force |
| **01** | Binary Search (Iterative) | $O(1)$ | $O(\log n)$ | $O(\log n)$ | $O(1)$ | Search |
| **01** | Binary Search (Recursive) | $O(1)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | Divide & Conquer |
| **02** | Min-Max (D&C) | $3n/2 - 2$ | $3n/2 - 2$ | $3n/2 - 2$ | $O(\log n)$ | Divide & Conquer |
| **02** | Merge Sort | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ | Divide & Conquer |
| **02** | Quick Sort | $O(n \log n)$ | $O(n \log n)$ | $O(n^2)$ | $O(\log n)$ | Divide & Conquer |
| **02** | Heap Sort | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(1)$ | Heap / In-place |
| **02** | Strassen Matrix Multiply | $O(n^{2.807})$ | $O(n^{2.807})$ | $O(n^{2.807})$ | $O(n^2)$ | Divide & Conquer |
| **03** | Fractional Knapsack | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ | Greedy |
| **03** | Job Sequencing | $O(n \log n)$ | $O(n \cdot d)$ | $O(n^2)$ | $O(d)$ | Greedy |
| **03** | Prim's Algorithm (Heap) | $O(E \log V)$ | $O(E \log V)$ | $O(E \log V)$ | $O(V)$ | Greedy |
| **03** | Kruskal's Algorithm (DSU)| $O(E \log V)$ | $O(E \log V)$ | $O(E \log V)$ | $O(V + E)$ | Greedy |
| **04** | Fibonacci (Memoized) | $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ | Dynamic Programming |
| **04** | Fibonacci (Tabulated) | $O(n)$ | $O(n)$ | $O(n)$ | $O(1)$ | Dynamic Programming |
| **04** | 0/1 Knapsack (DP) | $O(n \cdot W)$ | $O(n \cdot W)$ | $O(n \cdot W)$ | $O(n \cdot W)$ | Dynamic Programming |
| **04** | Multistage Graph | $O(V + E)$ | $O(V + E)$ | $O(V + E)$ | $O(V)$ | Dynamic Programming |
| **04** | Floyd-Warshall | $O(V^3)$ | $O(V^3)$ | $O(V^3)$ | $O(V^2)$ | Dynamic Programming |
| **04** | Bellman-Ford | $O(V \cdot E)$ | $O(V \cdot E)$ | $O(V \cdot E)$ | $O(V)$ | Dynamic Programming |
| **04** | TSP (Held-Karp) | $O(n^2 2^n)$ | $O(n^2 2^n)$ | $O(n^2 2^n)$ | $O(n 2^n)$ | Dynamic Programming |
| **05** | Tree Traversals | $O(n)$ | $O(n)$ | $O(n)$ | $O(h)$ | Tree Traversal |
| **05** | BFS Graph Traversal | $O(V + E)$ | $O(V + E)$ | $O(V + E)$ | $O(V)$ | Queue Traversal |
| **05** | DFS Graph Traversal | $O(V + E)$ | $O(V + E)$ | $O(V + E)$ | $O(V)$ | Stack Traversal |
| **06** | 4-Queens / N-Queens | $O(N!)$ | $O(N! / c^N)$ | $O(N!)$ | $O(N)$ | Backtracking |
| **06** | Sum of Subsets | $O(2^n)$ | $O(2^n / \alpha)$ | $O(2^n)$ | $O(n)$ | Backtracking |
| **06** | Sudoku Solver (9x9) | $O(9^m)$ | $O(9^{m'})$ | $O(9^m)$ | $O(1)$ | Backtracking |
| **07** | Exhaustive Knapsack | $O(2^n)$ | $O(2^n)$ | $O(2^n)$ | $O(n)$ | Brute Force |
| **07** | Knapsack Branch & Bound | $O(n)$ | $O(2^{n/2})$ | $O(2^n)$ | $O(2^n)$ | Branch and Bound |
| **07** | TSP Branch & Bound | $O(n^2)$ | $O(c^n)$ | $O(n!)$ | $O(n^2 \cdot 2^n)$| Branch and Bound |
