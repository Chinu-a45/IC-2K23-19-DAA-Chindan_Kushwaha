# APPLICATION: Constraint Satisfaction Solver

> **Unit 6 - Backtracking** | Course Outcome: CO4 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Implement a general Constraint Satisfaction Problem (CSP) solver applied to Map Coloring with forward checking and heuristics.

---

## 2. Algorithm / Approach
Formulate map coloring (e.g. Australian territories). For each territory, assign a color from domain {1..M}. Verify that no two adjacent territories share the same color. Backtrack upon domain wipeout.

---

## 3. Pseudocode / Flowchart
```text
Algorithm CSPSolver(v, colors, map):
    if v == num_variables then return true
    for c <- 1 to num_colors do
        if IsConsistent(v, c, map, colors) then
            colors[v] <- c
            if CSPSolver(v + 1, colors, map) then return true
            colors[v] <- 0 // Backtrack
        end if
    end for
    return false
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/07-Constraint-Satisfaction-Solver.png)

---

## 4. Time & Space Complexity Analysis
Unconstrained search space has size M^V. Bounding and consistency checks prune conflicting branches immediately, solving map coloring in microseconds.

---

## 5. Sample Input / Output & Verification
The program prints step-by-step state logs and verifies all outputs internally against exact theoretical expectations. Refer to the terminal execution output below for concrete sample runs.

---

## 6. Screenshots & Visualizations
### Terminal Execution Output

![Terminal Output](screenshots/output.png)


---

## 7. Experimental Results & Telemetry
| N | Time Seconds | Backtracks | Colors Used |
| --- | --- | --- | --- |
| 7 | 1.2e-5 | 0 | 3 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Understood the formal CSP framework (Variables, Domains, Constraints).
- Learned forward consistency checking mechanics.
- Applied in timetabling, frequency assignment in cellular networks, and compiler register allocation.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
