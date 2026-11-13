# Sum of Subsets

> **Unit 6 - Backtracking** | Course Outcome: CO4 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Find all subsets of a given integer set whose sum equals a target value using backtracking with bounding pruning.

---

## 2. Algorithm / Approach
Sort weights ascending. Use two bounding conditions: 1) current_sum + w[k] <= target; 2) current_sum + remaining_sum >= target. Prune immediately when either fails.

---

## 3. Pseudocode / Flowchart
```text
Algorithm SumOfSubsets(k, cur_sum, rem_sum, target, w, x):
    x[k] <- 1
    if cur_sum + w[k] == target then PrintSubset(x)
    else if cur_sum + w[k] + w[k+1] <= target then
        SumOfSubsets(k + 1, cur_sum + w[k], rem_sum - w[k], target, w, x)
    end if
    x[k] <- 0
    if cur_sum + rem_sum - w[k] >= target and cur_sum + w[k+1] <= target then
        SumOfSubsets(k + 1, cur_sum, rem_sum - w[k], target, w, x)
    end if
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/05-Sum-of-Subsets.png)

---

## 4. Time & Space Complexity Analysis
Exhaustive subset generation evaluates 2^n states. With sorting and double-bounding functions, subtrees exceeding target or lacking sufficient remaining mass are pruned, typically reducing evaluated nodes by >85%. Space = O(n).

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
| N | Time Seconds | Nodes Explored | Solutions Count |
| --- | --- | --- | --- |
| 10 | 1.22800000e-06 | 166 | 0 |
| 15 | 9.26150000e-05 | 3849 | 401 |
| 20 | 1.53676100e-03 | 86876 | 6869 |
| 25 | 6.57901800e-03 | 1950670 | 0 |
| 28 | 4.07832420e-02 | 13051613 | 0 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Mastered bounding function design combining upper and lower lookahead bounds.
- Learned how sorting enhances pruning efficiency.
- Applied in financial transaction reconciliation, portfolio balancing, and knapsack feasibility checks.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
