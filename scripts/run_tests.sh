#!/bin/bash

# K-Means Performance Test Script

# Overwrite results file with header
echo "n k threads time" > results.dat

# Dataset sizes (increasing workload)
DATASETS=(10000 50000 100000 500000 1000000)

# Thread counts to test scalability
THREADS=(1 2 4 8)

# Fixed number of clusters
K=5

# Loop through dataset sizes
for n in "${DATASETS[@]}"
do
    # Loop through thread counts
    for t in "${THREADS[@]}"
    do
        # Display progress in terminal
        echo "Running dataset size = $n with $t threads"

        # Run program and append output to results file
        ./kmeans $n $K $t >> results.dat
    done
done


