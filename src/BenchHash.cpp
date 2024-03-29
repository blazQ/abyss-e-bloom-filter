#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <nthash/nthash.hpp>
#include "MurmurHash3.h"
#include <city.h>

std::string generateRandomDNASequence(int length) {
    srand(time(0));

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
        std::cerr << "Usage: " << argv[0] << " <sequence_length> <number_of_iterations> <k> <hashes_per_k-mer>" << std::endl;
        return 1;
    }

    /** TEST DI NTHASH **/
    int seqLen = std::atoi(argv[1]);
    int iterations = std::atoi(argv[2]);
    int k = std::atoi(argv[3]);
    int num_hashes = std::atoi(argv[4]);

    std::string randomDNASequence = generateRandomDNASequence(seqLen);
   /* std::cout << "Random DNA sequence of length " << seqLen << " bp: " << std::endl << randomDNASequence << std::endl;
    std::cout << "Commencing ntHash2 benchmarking using this random sequence for " << iterations << " iterations on " << k << "-mers" << " hashed " << num_hashes << " times" << std::endl;*/

    auto start_nt = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < iterations; i++) {
        nthash::NtHash nth(randomDNASequence, num_hashes, k);
            while (nth.roll()) {
                //std::cout << nth.hashes()[0] << std::endl;
                // nth.hashes()[0] = First k-mer first hash
                // nth.hashes()[1] = First k-mer second hash
                // nth.hashes()[2] = First k-mer third hash
                // nth.hashes()[3] = Second k-mer first hash
                // ecc
            }
    }

    auto stop_nt = std::chrono::high_resolution_clock::now();
    auto duration_nt = std::chrono::duration_cast<std::chrono::microseconds>(stop_nt - start_nt);

    //std::cout << "Tempo trascorso: " << duration_nt.count() << " microsecondi" << std::endl;
    /* TODO: Aggiungi una modalità verbose se il codice è richiamato senza script */

    /** TEST DI MURMURHASH3 **/
    //std::cout << "Commencing Murmurhash3 benchmarking using this random sequence for " << iterations << " iterations on " << k << "-mers" << " hashed " << num_hashes << " times" << std::endl
    uint64_t hashValue[2];
    auto start_mur = std::chrono::high_resolution_clock::now();
    // For each iteration
    for(int i = 0; i < iterations; i++) {
            // Hash all k-mers, num_hashes times
            for (int i = 0; i <= seqLen - k; ++i) {
                // Get pointer to string buffer
                std::string current_kmer = randomDNASequence.substr(i, k);
                const void* keyPtr = static_cast<const void*>(current_kmer.c_str());
                    for(int j = 0; j < num_hashes; j++){
                        MurmurHash3_x64_128(keyPtr, k, 0, &hashValue);
                    }
            }
    }

    auto stop_mur = std::chrono::high_resolution_clock::now();
    auto duration_mur = std::chrono::duration_cast<std::chrono::microseconds>(stop_mur - start_mur);
    //std::cout << "Tempo trascorso: " << duration_mur.count() << " microsecondi" << std::endl;


    /** TEST DI CITYHASH **/
    //std::cout << "Commencing CityHash benchmarking using this random sequence for " << iterations << " iterations on " << k << "-mers" << " hashed " << num_hashes << " times" << std::endl;
    auto start_city = std::chrono::high_resolution_clock::now();
    // For each iteration
    for(int i = 0; i < iterations; i++) {
            // Hash all k-mers, num_hashes times
            for (int i = 0; i <= seqLen - k; ++i) {
                // Get pointer to string buffer
                std::string current_kmer = randomDNASequence.substr(i, k);
                const void* keyPtr = static_cast<const void*>(current_kmer.c_str());
                    for(int j = 0; j < num_hashes; j++){
                        CityHash128(randomDNASequence.c_str(), seqLen);
                    }
            }
    }

    auto stop_city = std::chrono::high_resolution_clock::now();
    auto duration_city = std::chrono::duration_cast<std::chrono::microseconds>(stop_city - start_city);
    //std::cout << "Tempo trascorso: " << duration_city.count() << " microsecondi" << std::endl;

    std::cout << duration_nt.count() << "," << duration_mur.count() << "," << duration_city.count() << std::endl;
    /*std::cout << "MurmurHash3 128-bit hash value: " << std::endl;
    std::cout << std::hex << hashValue[0] << hashValue[1] << std::endl;*/

    return 0;
}
