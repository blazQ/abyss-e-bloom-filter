#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <nthash/nthash.hpp>

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

    /** TEST DI NTHASH **/
    int seqLen = std::atoi(argv[1]);
    int iterations = std::atoi(argv[2]);
    int k = std::atoi(argv[3]);
    int num_hashes = std::atoi(argv[4]);


    srand(time(0));
    for(int i = 0; i < iterations; i++){
        std::string current_sequence = generateRandomDNASequence(seqLen);
        nthash::NtHash nth(current_sequence, num_hashes, k);
        while (nth.roll()) {
            for(int i = 0; i < num_hashes; i++){
                std::cout << nth.hashes()[i] << std::endl;
            }
        }
    }
}
