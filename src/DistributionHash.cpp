#include <iostream>
#include <iterator>
#include <ostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <nthash/nthash.hpp>
#include <utility>
#include "MurmurHash3.h"
#include "city.h"

std::string generateRandomDNASequence(int length) {
    const std::string bases = "ACGT";
    std::string sequence;

    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % 4; // Generate random index in the range [0, 3]
        sequence += bases[randomIndex];
    }

    return sequence;
}


int main(int argc, char* argv[]){

    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <seq_length> <number_of_iterations> <k> <hashes_per_k-mer>" << std::endl;
        return 1;
    }

    std::ofstream ntHashDis("ntHashDis.csv");
    std::ofstream murmurDis("murmurDis.csv");
    std::ofstream cityDis("cityDis.csv");

    std::ostream& ntHashDisOut = ntHashDis;
    std::ostream& murmurDisOut = murmurDis;
    std::ostream& cityDisOut = cityDis;

    int seqLen = std::atoi(argv[1]);
    int iterations = std::atoi(argv[2]);
    int k = std::atoi(argv[3]);
    int num_hashes = std::atoi(argv[4]);

    srand(time(0));

    /** TEST DI NTHASH **/
    for(int i = 0; i < iterations; i++){
        std::string current_sequence = generateRandomDNASequence(seqLen);
        nthash::NtHash nth(current_sequence, num_hashes, k);
        while (nth.roll()) {
            for(int i = 0; i < num_hashes; i++){
                ntHashDisOut << nth.hashes()[i] << std::endl;
            }
        }
    }

    /**MURMURHASH3 TEST*/
    uint32_t hashValue;
    // For each iteration
    for(int i = 0; i < iterations; i++) {
        std::string current_sequence = generateRandomDNASequence(seqLen);
            // Hash all k-mers, num_hashes times
            for (int i = 0; i <= seqLen - k; ++i) {
                // Get pointer to string buffer
                std::string current_kmer = current_sequence.substr(i, k);
                const void* keyPtr = static_cast<const void*>(current_kmer.c_str());
                       MurmurHash3_x86_32(keyPtr, k, 0, &hashValue);
                       murmurDisOut<< hashValue << std::endl;
            }
    }

    /**CITYHASH TEST*/

    for(int i = 0; i < iterations; i++) {
         std::string current_sequence = generateRandomDNASequence(seqLen);
            // Hash all k-mers, num_hashes times
            for (int i = 0; i <= seqLen - k; ++i) {
                // Get pointer to string buffer
                std::string current_kmer = current_sequence.substr(i, k);
                        cityDisOut << CityHash64(current_kmer.c_str(), seqLen)<<std::endl;
            }
    }
}
