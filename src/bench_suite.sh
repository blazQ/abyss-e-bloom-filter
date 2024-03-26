# Define the name of your C++ program executable
PROGRAM="hash.out"

if [ "$#" -ne 5 ]; then
    echo "Usage: $0 <base_pair> <iterations> <k> <num_hashes>"
    exit 1
fi

BASE_PAIR="$1"
ITERATIONS="$2"
K="$3"
NUM_HASHES="$4"
OUTPUT_FILE="$5"

echo "ntHash2,Murmur3,CityHash128" > "$OUTPUT_FILE"

# Define the arguments you want to pass to your C++ program
# Each entry in ARGS represents a set of parameters for one execution
ARGS=()

# Loop to construct argument strings with the second number doubled each time
for ((i = 0; i < 5; i++)); do
    # Calculate the doubled value for ITERATIONS
    DOUBLED_ITERATIONS=$((ITERATIONS * (2 ** i)))
    # Construct the argument string and add it to the array
    ARGS+=("$BASE_PAIR $DOUBLED_ITERATIONS $K $NUM_HASHES")
done

# Print the constructed arguments for verification
for arg in "${ARGS[@]}"; do
    ./"$PROGRAM" $arg >> "$OUTPUT_FILE"
done
