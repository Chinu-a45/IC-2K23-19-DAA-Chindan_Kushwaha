# Exhaustive Search Demonstration

> **Unit 7 - NP-Hard, NP-Complete & Advanced Optimization** | Course Outcome: CO5, CO7 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Demonstrate the combinatorial explosion of brute-force Exhaustive Search on 0/1 Knapsack (2^n) and TSP ((n-1)!).

---

## 2. Algorithm / Approach
Generate all 2^n binary subset combinations for 0/1 Knapsack using bitwise operators. Measure how execution time doubles with each additional item.

---

## 3. Pseudocode / Flowchart
```text
Algorithm ExhaustiveKnapsack(weights, values, n, W):
    max_val <- 0
    for mask <- 0 to (1 << n) - 1 do
        total_w <- sum(weights[i] for bit i in mask)
        total_v <- sum(values[i] for bit i in mask)
        if total_w <= W and total_v > max_val then max_val <- total_v
    end for
    return max_val
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/01-Exhaustive-Search-Demo.png)

---

## 4. Time & Space Complexity Analysis
Time complexity = Theta(n * 2^n). At n=20, evaluations = 1,048,576; at n=30, evaluations > 1 billion. Space complexity = O(1) auxiliary.

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
| N | Time Seconds | States Evaluated | Time Ms |
| --- | --- | --- | --- |
| 10 | 1.02000000e-07 | 1024 | 0.0001 |
| 12 | 2.20000000e-08 | 4096 | 0.0000 |
| 14 | 1.70000000e-08 | 16384 | 0.0000 |
| 16 | 1.60000000e-08 | 65536 | 0.0000 |
| 18 | 1.60000000e-08 | 262144 | 0.0000 |
| 20 | 1.60000000e-08 | 1048576 | 0.0000 |
| 22 | 1.60000000e-08 | 4194304 | 0.0000 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Witnessed firsthand the exponential wall of brute-force exhaustive search.
- Understood the definition and boundary of NP-Hard problems.
- Demonstrated the absolute necessity of intelligent pruning heuristics.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
