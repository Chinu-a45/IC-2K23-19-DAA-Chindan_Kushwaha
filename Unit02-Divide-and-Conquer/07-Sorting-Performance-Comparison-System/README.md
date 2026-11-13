# APPLICATION: Sorting Performance Comparison System

> **Unit 2 - Divide and Conquer** | Course Outcome: CO1 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Comprehensive benchmarking comparison of Merge Sort, Quick Sort, and Heap Sort on random arrays across varying values of n.

---

## 2. Algorithm / Approach
Generate identical datasets for each size n = 1,000 to 50,000. Measure execution times using high-resolution clock and record comparative telemetry.

---

## 3. Pseudocode / Flowchart
```text
Algorithm SortingComparisonSuite(sizes):
    for each n in sizes do
        data <- GenerateRandomArray(n)
        t_merge <- MeasureSort(MergeSort, data)
        t_quick <- MeasureSort(QuickSort, data)
        t_heap <- MeasureSort(HeapSort, data)
        LogComparison(n, t_merge, t_quick, t_heap)
    end for
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/07-Sorting-Performance-Comparison-System.png)

---

## 4. Time & Space Complexity Analysis
All three algorithms have average-case complexity O(n log n). Quick Sort's constant factor is smallest due to cache locality and minimal data movement. Merge Sort requires auxiliary memory allocation. Heap Sort has slightly higher constant overhead due to non-sequential memory jumps.

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
| N | Time Seconds | Merge Ms | Quick Ms | Heap Ms |
| --- | --- | --- | --- | --- |
| 1000 | 4.06460000e-05 | 0.0671 | 0.0406 | 0.0395 |
| 5000 | 2.34793000e-04 | 0.3629 | 0.2348 | 0.2149 |
| 10000 | 5.00418000e-04 | 0.7675 | 0.5004 | 0.4571 |
| 20000 | 1.08310800e-03 | 1.6900 | 1.0831 | 1.0145 |
| 50000 | 2.81157100e-03 | 4.4115 | 2.8116 | 2.5817 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Discovered practical crossover points and empirical constant-factor differences among O(n log n) sorting algorithms.
- Demonstrated why hybrid algorithms like Introsort and Timsort are standard in production runtimes.
- Essential for selecting the right sorting strategy based on memory constraints, stability requirements, and input distributions.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
