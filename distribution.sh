PROGRAM="DistributionHash.out"

if [ "$#" -ne 4 ]; then
    echo "Usage: $0 <base_pair> <iterations> <k> <num_hashes>"
    exit 1
fi

BASE_PAIR="$1"
ITERATIONS="$2"
K="$3"
NUM_HASHES="$4"

# Each entry in ARGS represents a set of parameters for one execution
ARGS=()

# Loop to construct argument strings with the second number doubled each time
ARGS=("$BASE_PAIR $ITERATIONS $K $NUM_HASHES")

for arg in "${ARGS[@]}"; do
    echo "Generating hash values for ${ITERATIONS} ${BASE_PAIR}bp sequences, assuming k = ${K} and hasing ${NUM_HASHES} times..."
    ./"$PROGRAM" $arg
    echo "Done!"
done
