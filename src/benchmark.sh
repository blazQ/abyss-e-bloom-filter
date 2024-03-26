#!/bin/bash

# Check if correct number of arguments are provided
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <base_pair> <iterations> <k>"
    exit 1
fi

# Get the base parameters from command line
BASE_PAIR="$1"
ITERATIONS="$2"
K="$3"

# Define the different NUM_HASHES values
NUM_HASHES_VALUES=("1" "3" "5")

# Loop over the different NUM_HASHES values
for NUM_HASHES in "${NUM_HASHES_VALUES[@]}"; do
    # Define the output file name based on NUM_HASHES
    OUTPUT_FILE="output_${NUM_HASHES}.csv"

    # Execute your original script with the current NUM_HASHES value
    ./bench_suite.sh "$BASE_PAIR" "$ITERATIONS" "$K" "$NUM_HASHES" "$OUTPUT_FILE"
done
