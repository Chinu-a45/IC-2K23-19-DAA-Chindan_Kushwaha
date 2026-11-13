# N-Queens Problem

> **Unit 6 - Backtracking** | Course Outcome: CO4 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Generalize the N-Queens solver for arbitrary board dimension N, evaluating solution count growth and execution scaling.

---

## 2. Algorithm / Approach
Parameterize board dimension N. Measure execution time and solution counts from N=4 to N=12.

---

## 3. Pseudocode / Flowchart
```text
Algorithm NQueens(row, N, board):
    if row == N then count++; return
    for col <- 0 to N - 1 do
        if IsSafe(board, row, col) then
            board[row] <- col
            NQueens(row + 1, N, board)
            board[row] <- -1
        end if
    end for
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/04-N-Queens.png)

---

## 4. Time & Space Complexity Analysis
Time complexity is O(N!), since queen placements are permutations with diagonal pruning. Space complexity is O(N) for the 1D board position vector.

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
| N | Time Seconds | Solutions | Nodes Explored | Time Ms |
| --- | --- | --- | --- | --- |
| 4 | 8.43000000e-07 | 2 | 17 | 0.0008 |
| 5 | 2.38200000e-06 | 10 | 54 | 0.0024 |
| 6 | 8.48400000e-06 | 4 | 153 | 0.0085 |
| 7 | 3.27620000e-05 | 40 | 552 | 0.0328 |
| 8 | 1.48851000e-04 | 92 | 2057 | 0.1489 |
| 9 | 5.98691000e-04 | 352 | 8394 | 0.5987 |
| 10 | 3.16427500e-03 | 724 | 35539 | 3.1643 |
| 11 | 1.60849490e-02 | 2680 | 166926 | 16.0849 |
| 12 | 8.40681390e-02 | 14200 | 856189 | 84.0681 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Analyzed combinatorial explosion: N=4 (2 solutions), N=8 (92), N=12 (14,200).
- Verified linear O(N) memory requirement.
- Benchmark testbed for combinatorial optimization algorithms.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
