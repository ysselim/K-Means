# Parallel K-Means Clustering Benchmark

A parallel implementation of the K-Means clustering algorithm in C using OpenMP. This project benchmarks how runtime changes as dataset size and thread count increase, demonstrating the impact of parallelization on a computationally intensive machine learning algorithm.

## Overview

K-Means is an unsupervised machine learning algorithm that groups data points into clusters based on their distance from cluster centroids. This project implements K-Means from scratch in C and parallelizes the point assignment step using OpenMP.

The program generates synthetic high-dimensional data, assigns points to the nearest centroid, updates cluster centroids, and measures execution time across different dataset sizes and thread counts.

## Features

- Implements K-Means clustering from scratch in C
- Uses OpenMP to parallelize the cluster assignment step
- Supports configurable dataset size, number of clusters, and thread count
- Generates synthetic 20-dimensional data points
- Uses dynamic memory allocation for large datasets
- Measures execution time using `omp_get_wtime()`
- Includes a Bash script to automate performance testing
- Produces benchmark results for scalability analysis

## Technologies Used

- C
- OpenMP
- Bash
- GCC
- Linux/macOS Terminal
- Gnuplot or another plotting tool for graph generation

## Project Structure

```text
parallel-kmeans/
│
├── kmeans.c
├── tests.sh
├── results.dat
├── execution_time.png
├── speedup.png
└── README.md
```

## How the Algorithm Works

The K-Means algorithm follows these main steps:

1. Generate synthetic data points.
2. Initialize the first `k` points as centroids.
3. Assign each point to the nearest centroid using Euclidean distance.
4. Recalculate each centroid as the mean of all points assigned to that cluster.
5. Repeat the assignment and update steps for a fixed number of iterations.

In this project, the assignment step is parallelized with OpenMP:

```c
#pragma omp parallel for schedule(static)
for (int i = 0; i < n; i++) {
    double min_dist = 1e9;
    int best_cluster = 0;

    for (int j = 0; j < k; j++) {
        double d = distance(&points[i], &centroids[j]);
        if (d < min_dist) {
            min_dist = d;
            best_cluster = j;
        }
    }

    points[i].cluster = best_cluster;
}
```

## Compilation

Compile the program with GCC and OpenMP support:

```bash
gcc -fopenmp kmeans.c -o kmeans -lm
```

The `-fopenmp` flag enables OpenMP parallelization, and `-lm` links the math library required for `sqrt()`.

## Usage

Run the program with:

```bash
./kmeans <num_points> <k_clusters> <threads>
```

Example:

```bash
./kmeans 1000000 5 4
```

This runs K-Means on 1,000,000 data points, using 5 clusters and 4 OpenMP threads.

The output format is:

```text
dataset_size clusters threads time
```

Example:

```text
1000000 5 4 14.203421
```

## Running Performance Tests

The included `tests.sh` script runs the program across multiple dataset sizes and thread counts.

Make the script executable:

```bash
chmod +x tests.sh
```

Run the script:

```bash
./tests.sh
```

The script tests:

```text
Dataset sizes: 10,000, 50,000, 100,000, 500,000, 1,000,000
Thread counts: 1, 2, 4, 8
Clusters: 5
```

Results are saved to:

```text
results.dat
```

## Results

The benchmark shows that execution time increases as dataset size grows, while additional threads reduce runtime by parallelizing the point assignment step.

### Execution Time vs Dataset Size

<img width="800" height="600" alt="scaling" src="https://github.com/user-attachments/assets/c777c79d-9199-48cb-8dce-9ac2ac0d1dbb" />

```markdown
![Execution Time vs Dataset Size](execution_time.png)
```

### Speedup vs Threads

<img width="800" height="600" alt="speedup" src="https://github.com/user-attachments/assets/27645807-2b4e-42a6-ae3f-7dd5bb08d773" />
```markdown
![Speedup vs Threads](speedup.png)
```

The speedup graph shows that performance improves from 1 to 4 threads, reaching approximately 3x speedup on the 1,000,000 point dataset. The speedup levels off at 8 threads, likely because only part of the algorithm is parallelized while the centroid update step remains sequential.

## Performance Summary

- The 1-thread version provides the baseline runtime.
- Increasing to 2 threads improves performance noticeably.
- Increasing to 4 threads provides the strongest speedup.
- Increasing to 8 threads shows limited additional improvement due to sequential portions of the algorithm.
- The results demonstrate both the benefits and limits of parallelization.

## Limitations

- The centroid update step is currently sequential.
- The program uses synthetic random data instead of a real dataset.
- Centroids are initialized using the first `k` points rather than a more advanced method such as K-Means++.
- The program runs for a fixed number of iterations instead of checking for convergence.

## Future Improvements

- Parallelize the centroid update step using per-thread partial sums
- Add convergence detection to stop when cluster assignments stabilize
- Implement K-Means++ centroid initialization
- Support loading datasets from CSV files
- Export final cluster assignments to a file
- Add more detailed benchmarking metrics such as efficiency and throughput

## Author

Created by Donya.

## License

This project is for educational purposes.
