#include <iostream>
#include <string>
#include <ctime>
#include "BloomFilter.h"
#include <nthash/nthash.hpp>
#include <unordered_set>
#include <utility>
#include <vector>
#include<random>


using namespace std;


string generateRandomDNASequence(size_t length) {
    const string bases = "ACGT";
    string sequence;

    for (size_t i = 0; i < length; ++i) {
        size_t randomIndex = rand() % 4; // Generate random index in the range [0, 3]
        sequence += bases[randomIndex];
    }

    return sequence;
}

int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <seq_length> <k> <numSequences> <num_hashes>" << std::endl;
        return 1;
    }

    const size_t sequenceLength = std::atoi(argv[1]);
    const size_t k = std::atoi(argv[2]);
    const size_t numSequences = std::atoi(argv[3]);
    const size_t numHashes = std::atoi(argv[4]);

    Bloomfilter<NtHashFunction<string> > ntFilter(numHashes, k);

    return 0;
}

