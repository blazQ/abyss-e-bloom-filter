#!/bin/bash

if [ "$#" -lt 5 ]; then
    echo "Usage: $0 <base_pair> <iterations> <num_sequences> <k> [num_hash_values...]"
    exit 1
fi

BASE_PAIR="$1"
ITERATIONS="$2"
NUM_SEQUENCES="$3"
K="$4"

shift 4  # Shift the first 4 arguments (base_pair, iterations, num_sequences k)

NUM_HASHES_VALUES=("$@")

for NUM_HASHES in "${NUM_HASHES_VALUES[@]}"; do

    OUTPUT_BENCHMARK="output_${NUM_HASHES}.csv"

    ./benchmark.sh "$BASE_PAIR" "$ITERATIONS" "$K" "$NUM_HASHES" "$OUTPUT_BENCHMARK"
    ./distribution.sh "$BASE_PAIR" "$NUM_SEQUENCES" "$K" "$NUM_HASHES"
done
