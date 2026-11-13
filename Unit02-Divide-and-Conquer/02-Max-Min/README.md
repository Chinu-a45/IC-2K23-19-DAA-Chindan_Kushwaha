# Maximum and Minimum using Divide and Conquer

> **Unit 2 - Divide and Conquer** | Course Outcome: CO1 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Find both the maximum and minimum elements in an array using Divide and Conquer with minimal comparisons.

---

## 2. Algorithm / Approach
Divide array at midpoint into two halves. Recursively compute (min1, max1) and (min2, max2). Combine with exactly 2 comparisons: overall_min = min(min1, min2) and overall_max = max(max1, max2).

---

## 3. Pseudocode / Flowchart
```text
Algorithm MaxMin(A, low, high):
    if low == high then return (A[low], A[low]) // 0 comps
    if high == low + 1 then // 1 comp
        if A[low] < A[high] then return (A[low], A[high])
        else return (A[high], A[low])
    mid <- (low + high) / 2
    (l_min, l_max) <- MaxMin(A, low, mid)
    (r_min, r_max) <- MaxMin(A, mid + 1, high)
    return (min(l_min, r_min), max(l_max, r_max)) // 2 comps
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/02-Max-Min.png)

---

## 4. Time & Space Complexity Analysis
Comparison recurrence: C(n) = 2*C(n/2) + 2 with C(2) = 1, C(1) = 0. Solving via substitution: C(n) = 2^k * C(n/2^k) + 2*(2^(k-1) - 1). For n=2^k: C(n) = 3n/2 - 2 comparisons. Standard sequential search requires 2n - 2 comparisons, achieving a 25% comparison reduction.

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
| N | Time Seconds | Comparisons | Theoretical Comparisons |
| --- | --- | --- | --- |
| 1000 | 3.74200000e-06 | 1510 | 1498 |
| 5000 | 1.76750000e-05 | 7950 | 7498 |
| 10000 | 4.00210000e-05 | 15902 | 14998 |
| 25000 | 1.06297000e-04 | 41382 | 37498 |
| 50000 | 1.61923000e-04 | 82766 | 74998 |
| 100000 | 5.71065000e-04 | 165534 | 149998 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Proved exact comparison count reduction from 2n - 2 to 3n/2 - 2.
- Learned how Divide and Conquer reduces total operations by combining base-case pairs.
- Applied in computer graphics bounding-box computation and statistical range tracking.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
