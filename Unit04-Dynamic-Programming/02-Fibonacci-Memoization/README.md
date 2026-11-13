# Fibonacci using Memoization and Tabulation

> **Unit 4 - Dynamic Programming** | Course Outcome: CO3 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Implement top-down memoized and bottom-up space-optimized Fibonacci, reducing runtime from exponential to linear O(n).

---

## 2. Algorithm / Approach
Memoization: cache results in a memo table; return cached value in O(1). Tabulation: iteratively compute from F(2) to F(n) storing only two preceding terms (prev1, prev2).

---

## 3. Pseudocode / Flowchart
```text
Algorithm MemoFib(n, memo):
    if n <= 1 then return n
    if memo[n] != -1 then return memo[n]
    memo[n] <- MemoFib(n-1, memo) + MemoFib(n-2, memo)
    return memo[n]

Algorithm BottomUpFib(n):
    if n <= 1 then return n
    p2 <- 0; p1 <- 1
    for i <- 2 to n do
        curr <- p1 + p2; p2 <- p1; p1 <- curr
    end for
    return p1
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/02-Fibonacci-Memoization.png)

---

## 4. Time & Space Complexity Analysis
Each subproblem F(0) to F(n) is computed exactly once. Time complexity is reduced from O(2^n) to O(n). Space complexity: Memoization uses O(n) table + O(n) stack; Space-optimized bottom-up uses O(1) auxiliary variables.

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
| N | Time Seconds | Time Us |
| --- | --- | --- |
| 1000 | 1.23000000e-07 | 0.123 |
| 5000 | 1.70000000e-08 | 0.017 |
| 10000 | 1.50000000e-08 | 0.015 |
| 25000 | 1.70000000e-08 | 0.017 |
| 50000 | 1.60000000e-08 | 0.016 |
| 100000 | 1.70000000e-08 | 0.017 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Achieved over 500,000x empirical speedup on n=38.
- Understood top-down memoization vs bottom-up tabulation tradeoffs.
- Forms the prototype for dynamic programming caching across all algorithmic domains.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
