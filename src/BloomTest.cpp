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

// Funzione per dividere una sequenza in k-mer
vector<string> splitIntoKmers(const string& sequence, size_t k) {
    vector<string> kmers;
    for (size_t i = 0; i <= sequence.length() - k; ++i) {
        kmers.push_back(sequence.substr(i, k));
    }
    return kmers;
}


int main() {
    /* TODO: Construct a dataset with more constraints and rules:
                    - Fairly sparse k-mer distribution in sequences
                    - Repeatable tests
        TODO: Flesh out the script, so certain parameters can be specified with command line arguments. */
    // Vector of pairs that contains a sequence and the list of its kmers
    vector<pair<string, vector<string> > > dataset;
    unordered_set<string> kmers;
    srand(time(0));

    const size_t sequenceLength = 250;
    const size_t k = 50;
    const size_t numSequences = 100000;

    for(size_t i = 0; i < numSequences; i++){
        string sequence = generateRandomDNASequence(sequenceLength);
        vector<string> kmers = splitIntoKmers(sequence, k);
        dataset.push_back(pair<string, vector<string> >(sequence, kmers));
    }

    Bloomfilter filter(1, 50);
    for(size_t i = 0; i < dataset.size()/2; i++){
        // insert sequence into bloom filter
        filter.insert(dataset[i].first);
        // mark its k-mers as done and dusted
        for(const auto& kmer: dataset[i].second){
            kmers.insert(kmer);
        }
    }

    uint64_t fp = 0;
    for(size_t i = dataset.size()/2; i < dataset.size(); i++){
        // It shouldn't, so if it does
        if(filter.contains(dataset[i].first)){
            // We check if its k-mers are inside the marked set
            for (const auto& kmer: dataset[i].second){
                if(kmers.find(kmer) == kmers.end()){
                    ++fp;
                    break;
                }
            }
        }
    }

    cout << fp/(dataset.size()/2) << endl;

    return 0;
}

