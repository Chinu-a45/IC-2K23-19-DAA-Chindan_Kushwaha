# Comprehensive Algorithm Pseudocode Reference

This directory contains formal Horowitz & Sahni / Cormen (CLRS) style pseudocode for all algorithms implemented in the repository across Units 01 through 07.

---

## Unit 1: Introduction to Algorithms & Performance Analysis

### 1. Euclid's Greatest Common Divisor (GCD)
```text
Algorithm EuclidGCD(a, b):
    Input: Non-negative integers a, b
    Output: Greatest common divisor of a and b
    while b != 0 do
        remainder <- a mod b
        a <- b
        b <- remainder
    end while
    return a
```

### 2. Iterative Binary Search
```text
Algorithm BinarySearchIterative(A, n, target):
    Input: Sorted array A[0...n-1], search key target
    Output: Index of target in A, or -1 if not found
    low <- 0
    high <- n - 1
    while low <= high do
        mid <- low + (high - low) / 2
        if A[mid] == target then
            return mid
        else if A[mid] < target then
            low <- mid + 1
        else
            high <- mid - 1
        end if
    end while
    return -1
```

### 3. Recursive Binary Search
```text
Algorithm BinarySearchRecursive(A, low, high, target):
    if low > high then
        return -1
    end if
    mid <- low + (high - low) / 2
    if A[mid] == target then
        return mid
    else if A[mid] > target then
        return BinarySearchRecursive(A, low, mid - 1, target)
    else
        return BinarySearchRecursive(A, mid + 1, high, target)
    end if
```

---

## Unit 2: Divide and Conquer

### 1. Max-Min Algorithm (Divide and Conquer)
```text
Algorithm MaxMin(A, low, high, min_val, max_val):
    if low == high then
        min_val <- A[low]
        max_val <- A[low]
    else if high == low + 1 then
        if A[low] < A[high] then
            min_val <- A[low]; max_val <- A[high]
        else
            min_val <- A[high]; max_val <- A[low]
        end if
    else
        mid <- (low + high) / 2
        MaxMin(A, low, mid, left_min, left_max)
        MaxMin(A, mid + 1, high, right_min, right_max)
        min_val <- min(left_min, right_min)
        max_val <- max(left_max, right_max)
    end if
```

### 2. Merge Sort
```text
Algorithm MergeSort(A, low, high):
    if low < high then
        mid <- low + (high - low) / 2
        MergeSort(A, low, mid)
        MergeSort(A, mid + 1, high)
        Merge(A, low, mid, high)
    end if

Algorithm Merge(A, low, mid, high):
    Create temporary array B[0...high-low]
    i <- low; j <- mid + 1; k <- 0
    while i <= mid and j <= high do
        if A[i] <= A[j] then B[k++] <- A[i++]
        else B[k++] <- A[j++]
    end while
    while i <= mid do B[k++] <- A[i++]
    while j <= high do B[k++] <- A[j++]
    Copy B back into A[low...high]
```

### 3. Quick Sort (Lomuto / Median Partition)
```text
Algorithm QuickSort(A, low, high):
    if low < high then
        pi <- Partition(A, low, high)
        QuickSort(A, low, pi - 1)
        QuickSort(A, pi + 1, high)
    end if

Algorithm Partition(A, low, high):
    pivot <- A[high]
    i <- low - 1
    for j <- low to high - 1 do
        if A[j] <= pivot then
            i <- i + 1
            swap(A[i], A[j])
        end if
    end for
    swap(A[i + 1], A[high])
    return i + 1
```

### 4. Heap Sort
```text
Algorithm HeapSort(A, n):
    // Build Max-Heap
    for i <- floor(n/2) - 1 down to 0 do
        Heapify(A, n, i)
    end for
    // Extract max root
    for i <- n - 1 down to 1 do
        swap(A[0], A[i])
        Heapify(A, i, 0)
    end for
```

### 5. Strassen's Matrix Multiplication
```text
Algorithm StrassenMultiply(A, B, n):
    if n <= 2 then return StandardMultiply(A, B)
    Partition A into A11, A12, A21, A22
    Partition B into B11, B12, B21, B22
    M1 <- Strassen((A11 + A22), (B11 + B22))
    M2 <- Strassen((A21 + A22), B11)
    M3 <- Strassen(A11, (B12 - B22))
    M4 <- Strassen(A22, (B21 - B11))
    M5 <- Strassen((A11 + A12), B22)
    M6 <- Strassen((A21 - A11), (B11 + B12))
    M7 <- Strassen((A12 - A22), (B21 + B22))
    C11 <- M1 + M4 - M5 + M7
    C12 <- M3 + M5
    C21 <- M2 + M4
    C22 <- M1 - M2 + M3 + M6
    return Combine(C11, C12, C21, C22)
```

---

## Unit 3: Greedy Method

### 1. Fractional Knapsack
```text
Algorithm FractionalKnapsack(Items, W):
    Sort Items descending by (value_i / weight_i)
    total_val <- 0.0
    for each item in Items do
        if item.weight <= W then
            total_val <- total_val + item.value
            W <- W - item.weight
        else
            total_val <- total_val + item.value * (W / item.weight)
            W <- 0
            break
        end if
    end for
    return total_val
```

### 2. Kruskal's MST
```text
Algorithm KruskalMST(V, E):
    Sort edges E ascending by weight
    Initialize Disjoint Set Union DSU(V)
    mst_edges <- empty list
    for each edge (u, v, w) in E do
        if DSU.find(u) != DSU.find(v) then
            DSU.unite(u, v)
            mst_edges.append((u, v, w))
            if size(mst_edges) == V - 1 then break
        end if
    end for
    return mst_edges
```

---

## Unit 4: Dynamic Programming

### 1. 0/1 Knapsack DP
```text
Algorithm Knapsack01DP(weights, values, n, W):
    Initialize DP[n+1][W+1] to 0
    for i <- 1 to n do
        for w <- 0 to W do
            if weights[i-1] <= w then
                DP[i][w] <- max(DP[i-1][w], values[i-1] + DP[i-1][w - weights[i-1]])
            else
                DP[i][w] <- DP[i-1][w]
            end if
        end for
    end for
    return DP[n][W]
```

### 2. Floyd-Warshall (All-Pairs Shortest Path)
```text
Algorithm FloydWarshall(dist, V):
    for k <- 0 to V - 1 do
        for i <- 0 to V - 1 do
            for j <- 0 to V - 1 do
                if dist[i][k] + dist[k][j] < dist[i][j] then
                    dist[i][j] <- dist[i][k] + dist[k][j]
                end if
            end for
        end for
    end for
    return dist
```

### 3. Held-Karp Traveling Salesperson Problem (TSP)
```text
Algorithm HeldKarpTSP(dist, n):
    Initialize DP[2^n][n] to INF
    DP[{0}][0] <- 0
    for mask <- 1 to 2^n - 1 do
        for u <- 0 to n - 1 do
            if u not in mask then continue
            for v <- 0 to n - 1 do
                if v not in mask then
                    next_mask <- mask | (1 << v)
                    DP[next_mask][v] <- min(DP[next_mask][v], DP[mask][u] + dist[u][v])
                end if
            end for
        end for
    end for
    return min_{u=1}^{n-1} { DP[(1<<n)-1][u] + dist[u][0] }
```

---

## Unit 6: Backtracking

### 1. General N-Queens Backtracking
```text
Algorithm NQueens(row, N, board):
    if row == N then
        RecordSolution(board)
        return
    end if
    for col <- 0 to N - 1 do
        if IsSafe(board, row, col) then
            board[row] <- col
            NQueens(row + 1, N, board)
            board[row] <- -1 // Backtrack
        end if
    end for
```

---

## Unit 7: Branch and Bound

### 1. Least-Cost 0/1 Knapsack Branch & Bound
```text
Algorithm KnapsackBranchAndBound(items, W):
    Sort items descending by value/weight ratio
    Initialize PriorityQueue PQ (Max-Heap by Upper Bound)
    u <- Node(level = -1, profit = 0, weight = 0, bound = FractionalRelaxation(u))
    PQ.push(u)
    max_profit <- 0
    while PQ is not empty do
        u <- PQ.pop()
        if u.bound <= max_profit then continue
        v.level <- u.level + 1
        // Branch 1: Include item v.level
        v.weight <- u.weight + items[v.level].weight
        v.profit <- u.profit + items[v.level].value
        if v.weight <= W and v.profit > max_profit then max_profit <- v.profit
        v.bound <- FractionalRelaxation(v)
        if v.bound > max_profit then PQ.push(v)
        // Branch 2: Exclude item v.level
        v.weight <- u.weight; v.profit <- u.profit
        v.bound <- FractionalRelaxation(v)
        if v.bound > max_profit then PQ.push(v)
    end while
    return max_profit
```
