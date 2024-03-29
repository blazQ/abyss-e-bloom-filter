#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "BloomFilter.h"
#include <nthash/nthash.hpp>
#include <vector>

std::string generateRandomDNASequence(int length) {
    const std::string bases = "ACGT";
    std::string sequence;

    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % 4; // Generate random index in the range [0, 3]
        sequence += bases[randomIndex];
    }

    return sequence;
}


int main() {
    /* TODO: Construct a dataset with more constraints and rules:
                    - Fairly sparse k-mer distribution in sequences
                    - Repeatable tests
        TODO: Flesh out the script, so certain parameters can be specified with command line arguments. */
    Bloomfilter bloomfilter(1, 50);
    std::vector<std::string> stringVec;

    for(int i = 0; i < 1000000; i++){
        std::string randomString = generateRandomDNASequence(250);
        stringVec.push_back(randomString);
    }

    for(int i = 0; i < 500000; i++){
        bloomfilter.insert(stringVec[i]);
    }

    for(int i = 500000; i < 1000000; i++){
        std::cout << bloomfilter.contains(stringVec[i]) << std::endl;
    }

    return 0;
}

