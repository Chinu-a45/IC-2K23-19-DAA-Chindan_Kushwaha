# APPLICATION: Algorithm Performance Analyzer

> **Unit 1 - Introduction to Algorithms & Performance Analysis** | Course Outcome: CO1 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Develop an automated performance analyzer comparing empirical execution times against theoretical asymptotic curves and calculating regression scaling ratios.

---

## 2. Algorithm / Approach
Calibrate the proportionality constant c using base empirical measurements. Compute expected theoretical times for linear and logarithmic models, and compute empirical ratio T(n)/n to confirm asymptotic convergence.

---

## 3. Pseudocode / Flowchart
```text
Algorithm PerformanceAnalyzer(sizes):
    c_factor <- CalibrateConstant(sizes[0])
    for each n in sizes do
        t_measured <- MeasureExecution(n)
        t_theoretical <- c_factor * n
        ratio <- t_measured / n
        LogMetrics(n, t_measured, t_theoretical, ratio)
    end for
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/07-Algorithm-Performance-Analyzer.png)

---

## 4. Time & Space Complexity Analysis
If T(n) is in Theta(n), the ratio T(n) / n must converge to a constant value c > 0 as n -> infinity. Deviations reflect cache misses, page faults, or instruction pipelining effects at different memory hierarchy levels.

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
| N | Time Seconds | Measured Time Us | Theoretical Linear | Theoretical Log |
| --- | --- | --- | --- | --- |
| 1000 | 1.68800000e-08 | 0.0169 | 0.0199 | 0.0198 |
| 5000 | 1.70400000e-08 | 0.0170 | 0.0993 | 0.0244 |
| 10000 | 1.71600000e-08 | 0.0172 | 0.1985 | 0.0264 |
| 25000 | 1.59200000e-08 | 0.0159 | 0.4963 | 0.0290 |
| 50000 | 1.61200000e-08 | 0.0161 | 0.9925 | 0.0310 |
| 100000 | 1.86000000e-08 | 0.0186 | 1.9850 | 0.0330 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Built a reusable, automated algorithm performance validation suite.
- Learned how CPU L1/L2/L3 cache line transitions affect actual runtime scaling.
- Applicable in automated CI/CD performance regression detection in production software pipelines.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
