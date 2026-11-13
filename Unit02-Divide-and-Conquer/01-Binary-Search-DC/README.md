# Binary Search (Divide and Conquer)

> **Unit 2 - Divide and Conquer** | Course Outcome: CO1 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Implement Divide and Conquer Binary Search, showing formal subproblem splits and base cases.

---

## 2. Algorithm / Approach
Divide: compute mid. Conquer: recursively search left half [low, mid-1] or right half [mid+1, high]. Combine: trivial since single element match completes the search.

---

## 3. Pseudocode / Flowchart
```text
Algorithm BinarySearchDC(A, low, high, key):
    if low > high then return -1
    mid <- low + (high - low) / 2
    if A[mid] == key then return mid
    if key < A[mid] then return BinarySearchDC(A, low, mid - 1, key)
    else return BinarySearchDC(A, mid + 1, high, key)
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/01-Binary-Search-DC.png)

---

## 4. Time & Space Complexity Analysis
Recurrence: T(n) = T(n/2) + O(1). By Master Theorem: a=1, b=2, f(n)=O(1) => T(n) = O(log n). Auxiliary space = O(log n) call stack.

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
| N | Time Seconds | Subproblems |
| --- | --- | --- |
| 1000 | 8.04000000e-09 | 8 |
| 2000 | 1.05550000e-08 | 11 |
| 5000 | 1.29800000e-08 | 10 |
| 10000 | 1.33150000e-08 | 13 |
| 25000 | 1.16400000e-08 | 12 |
| 50000 | 1.69800000e-08 | 16 |
| 100000 | 1.40750000e-08 | 14 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Understood formal Divide-and-Conquer components: Divide, Conquer, Combine.
- Verified subproblem count equals 1 per recursive stage.
- Applied in binary partitioned search spaces and root-finding algorithms (e.g. bisection method).

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
