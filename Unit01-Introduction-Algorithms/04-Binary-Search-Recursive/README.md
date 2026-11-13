# Recursive Binary Search

> **Unit 1 - Introduction to Algorithms & Performance Analysis** | Course Outcome: CO1 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Implement recursive binary search using divide-and-conquer recurrence relation and trace call stack recursion depth.

---

## 2. Algorithm / Approach
Express binary search as a recursive subproblem: BinarySearch(A, low, high, target) divides into either BinarySearch(A, low, mid-1, target) or BinarySearch(A, mid+1, high, target) with base condition low > high.

---

## 3. Pseudocode / Flowchart
```text
Algorithm BinarySearchRecursive(A, low, high, target):
    if low > high then return -1
    mid <- low + (high - low) / 2
    if A[mid] == target then return mid
    else if A[mid] > target then
        return BinarySearchRecursive(A, low, mid - 1, target)
    else
        return BinarySearchRecursive(A, mid + 1, high, target)
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/04-Binary-Search-Recursive.png)

---

## 4. Time & Space Complexity Analysis
The recurrence relation is T(n) = T(n/2) + O(1), with base case T(1) = O(1). By Master Theorem: a = 1, b = 2, f(n) = O(1). Since n^(log_b a) = n^0 = 1 = f(n), by Master Theorem Case 2: T(n) = O(log n). Recursion stack uses O(log n) auxiliary space.

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
| N | Time Seconds | Depth |
| --- | --- | --- |
| 1000 | 3.55000000e-08 | 10 |
| 2000 | 3.29400000e-08 | 9 |
| 5000 | 3.84850000e-08 | 12 |
| 10000 | 3.62900000e-08 | 11 |
| 20000 | 4.14850000e-08 | 14 |
| 50000 | 3.99150000e-08 | 13 |
| 100000 | 6.53100000e-08 | 17 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Mastered recursive divide-and-conquer subproblem formulation and termination condition design.
- Compared call stack overhead vs iterative loops; noted recursive call frames require O(log n) stack memory.
- Applied in hierarchical binary search trees, IP routing prefix lookup, and Git bisect debugging.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
