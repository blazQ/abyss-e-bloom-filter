PROGRAM="BenchHash.out"

if [ "$#" -ne 5 ]; then
    echo "Usage: $0 <base_pair> <iterations> <k> <num_hashes> <output_file>"
    exit 1
fi

BASE_PAIR="$1"
ITERATIONS="$2"
K="$3"
NUM_HASHES="$4"
OUTPUT_FILE="$5"

echo "ntHash2,Murmur3,CityHash128" > "$OUTPUT_FILE"

# Each entry in ARGS represents a set of parameters for one execution
ARGS=()

# Loop to construct argument strings with the second number doubled each time
for ((i = 0; i < 5; i++)); do
    DOUBLED_ITERATIONS=$((ITERATIONS * (2 ** i)))
    ARGS+=("$BASE_PAIR $DOUBLED_ITERATIONS $K $NUM_HASHES")
done

for arg in "${ARGS[@]}"; do
    ./"$PROGRAM" $arg >> "$OUTPUT_FILE"
done
