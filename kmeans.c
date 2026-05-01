#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define MAX_ITER 100      // number of iterations for convergence
#define DIM 20            // dimensionality of each data point

// Structure representing a data point
typedef struct {
    double x[DIM];      // coordinates
    int cluster;        // assigned cluster index
} Point;

// Compute Euclidean distance between two points
double distance(Point *a, Point *b) {
    double sum = 0.0;
    for (int i = 0; i < DIM; i++) {
        double diff = a->x[i] - b->x[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

// Generate synthetic dataset (random points in [0,1])
void generate_points(Point *points, int n) {
    for (int i = 0; i < n; i++) {
        for (int d = 0; d < DIM; d++) {
            points[i].x[d] = (double)rand() / RAND_MAX;
        }
        points[i].cluster = -1;  // unassigned initially
    }
}

int main(int argc, char *argv[]) {

    // Expect: number of points, number of clusters, thread count
    if (argc < 4) {
        printf("Usage: %s <num_points> <k_clusters> <threads>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);   // dataset size
    int k = atoi(argv[2]);   // number of clusters
    int threads = atoi(argv[3]); // OpenMP threads

    omp_set_num_threads(threads);

    // Allocate memory for dataset and centroids
    Point *points = malloc(n * sizeof(Point));
    Point *centroids = malloc(k * sizeof(Point));

    srand(42); // fixed seed for reproducibility
    generate_points(points, n);

    // Initialize centroids using first k points
    for (int i = 0; i < k; i++) {
        centroids[i] = points[i];
    }

    double start = omp_get_wtime();

    // Main K-Means loop
    for (int iter = 0; iter < MAX_ITER; iter++) {

        // --- Assignment step (parallel) ---
        // Each thread assigns points to nearest centroid
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

        // --- Update step (sequential for correctness) ---
        // Compute new centroids as mean of assigned points
        double sum[k][DIM];
        int count[k];

        // Initialize accumulators
        for (int i = 0; i < k; i++) {
            count[i] = 0;
            for (int d = 0; d < DIM; d++)
                sum[i][d] = 0.0;
        }

        // Accumulate sums
        for (int i = 0; i < n; i++) {
            int c = points[i].cluster;
            count[c]++;
            for (int d = 0; d < DIM; d++)
                sum[c][d] += points[i].x[d];
        }

        // Compute new centroids
        for (int i = 0; i < k; i++) {
            if (count[i] == 0) continue;
            for (int d = 0; d < DIM; d++)
                centroids[i].x[d] = sum[i][d] / count[i];
        }
    }

    double end = omp_get_wtime();

    // Output format: dataset_size clusters threads time
    printf("%d %d %d %.6f\n", n, k, threads, end - start);

    free(points);
    free(centroids);

    return 0;
}