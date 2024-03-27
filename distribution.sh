PROGRAM="DistributionHash.out"

if [ "$#" -ne 5 ]; then
    echo "Usage: $0 <base_pair> <iterations> <k> <num_hashes> <output_file>"
    exit 1
fi

BASE_PAIR="$1"
ITERATIONS="$2"
K="$3"
NUM_HASHES="$4"
OUTPUT_FILE="$5"

echo "HashValues" > "$OUTPUT_FILE"

# Each entry in ARGS represents a set of parameters for one execution
ARGS=()

# Loop to construct argument strings with the second number doubled each time
ARGS=("$BASE_PAIR $ITERATIONS $K $NUM_HASHES")

for arg in "${ARGS[@]}"; do
    ./"$PROGRAM" $arg >> "$OUTPUT_FILE"
done
