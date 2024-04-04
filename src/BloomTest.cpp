#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "BloomFilter.h"
#include <nthash/nthash.hpp>
#include <vector>
#include<random>

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
    /*
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
    */
    size_t hash_func_count = 1;
    size_t k_size = 50;
    Bloomfilter bloom_filter(hash_func_count, k_size);

    // Inserimento dei dati nel Bloom filter
    std::vector<std::string> dataset;
   for(int i = 0; i < 1000000; i++){
        std::string randomString = generateRandomDNASequence(250);
        dataset.push_back(randomString);
    }
    for (int i = dataset.size()/2; i < dataset.size(); i++ ) {
        bloom_filter.insert(dataset[i]);
    }

    // Test dei dati casuali
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, dataset.size()/2);
    size_t num_random_tests = 10000;
    size_t false_positives = 0;

    for (size_t i = 0; i < num_random_tests; ++i) {
        // Genera dato casuale
        size_t random_index = dis(gen);
        std::string random_data = dataset[random_index];
        // Verifica se il Bloom filter identifica erroneamente il dato casuale come presente
        if (bloom_filter.contains(random_data)) {
            false_positives++;
        }
    }
    std::cout<<"Number of false positives: "<<false_positives<<std::endl;
    // Calcolo della probabilità di falsi positivi
    double false_positive_probability = static_cast<double>(false_positives) / num_random_tests;
    std::cout << "Probabilita' di falsi positivi: " << false_positive_probability << std::endl;


    return 0;
}

