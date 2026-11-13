# Breadth First Search

> **Unit 5 - Basic Traversal & Search Techniques** | Course Outcome: CO6 | IC-709 B Design & Analysis of Algorithms Lab

---

## 1. Problem Statement
Implement Breadth First Search (BFS) using std::queue and compute shortest hop path distances in unweighted graphs.

---

## 2. Algorithm / Approach
Initialize visited array and queue with source. While queue not empty, dequeue u, visit all unvisited neighbors, set dist[v] = dist[u] + 1, and enqueue.

---

## 3. Pseudocode / Flowchart
```text
Algorithm BFS(V, adj, src):
    visited <- array of size V initialized to false
    dist <- array of size V initialized to -1
    q.push(src); visited[src] <- true; dist[src] <- 0
    while not q.empty() do
        u <- q.pop()
        for each v in adj[u] do
            if not visited[v] then
                visited[v] <- true; dist[v] <- dist[u] + 1
                q.push(v)
            end if
        end for
    end while
    return dist
```

### Algorithm Flowchart
![Flowchart](../../docs/algorithm-flowcharts/06-BFS.png)

---

## 4. Time & Space Complexity Analysis
Every vertex is enqueued and dequeued once: O(V). Every edge is scanned once: O(E). Total time complexity = O(V + E). Space complexity = O(V) for queue and visited arrays.

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
| N | Time Seconds | Time Ms |
| --- | --- | --- |
| 500 | 2.30760000e-05 | 0.0231 |
| 1000 | 2.99200000e-05 | 0.0299 |
| 2500 | 6.05340000e-05 | 0.0605 |
| 5000 | 1.41574000e-04 | 0.1416 |
| 10000 | 1.85623000e-04 | 0.1856 |
| 25000 | 7.93077000e-04 | 0.7931 |


The empirical scaling strictly conforms to theoretical asymptotic bounds, as captured in `results.csv`.

---

## 8. Learning Outcomes & Real-World Applications
- Proved that BFS guarantees shortest path in unweighted graphs.
- Understood level-order wavefront traversal mechanics.
- Applied in social network degrees of separation (LinkedIn connections), web crawling, and peer-to-peer routing.

---

## 9. How to Compile & Run
Execute the following commands in this directory:
```bash
g++ -std=c++17 -O2 main.cpp -o main
./main
```
