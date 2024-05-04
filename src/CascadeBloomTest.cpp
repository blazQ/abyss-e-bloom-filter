#include <iostream>
#include <string>
#include <ctime>
#include "CascadeBloomFilter.h"
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

/***
How this test works:
The CascadeBloomFilter we implemented was actually the first bloom filter we coded.
The only hash function available here is nthash, used in a naive way (the default one).
While in the more generic bloom filter we store the hash value for the whole string inside the filter, this time we store k-mers.
This is done because the hash function computes hash values for every k-mer, and does it so num_hashes times (where num_hashes is a function argument).
In the more generic bloom filter we used an option to obtain the hash value for the whole string (which is derived from the hash value of every kmer and only available after looping through them all).
But that is not a "real application scenario", since the bloom filter would be used during genome assembly, where k-mers (not strings) are stored in the filter as nodes of an embedded de Bruijn graph.
The CascadeBloomFilter that is used here is instead more akin to the actual concept.
The thing is that it is more difficult to test, because as the size of the dataset increases, since the insertion criteria is k-mers and not strings, false positive rate isn't
the ratio between false positive strings / number of strings tested, but is instead the ratio between k-mers false positives / k-mers tested, which we do not know a priori
since they are randomly generated.
Another thing to note is that this program lets you specify the number of sequences, but for every sequence you have k k-mers.
****/

int main(int argc, char* argv[]) {

    if (argc != 6) {
        cerr << "Usage: " << argv[0] << " <seq_length> <k> <numSequences> <num_hashes> <filter_size>" << endl;
        return 1;
    }

    const size_t sequenceLength = atoi(argv[1]);
    const size_t k = atoi(argv[2]);
    const size_t numSequences = atoi(argv[3]);
    const size_t numHashes = atoi(argv[4]);
    const size_t filterSize = atoi(argv[5]);


    // Vector of pairs that contains a sequence and the list of its kmers
    vector<pair<string, vector<string>>> dataset;
    unordered_set<string> kmers;
    unordered_set<string> global_kmers;
    srand(time(0));

    for(size_t i = 0; i < numSequences; i++){
        string sequence = generateRandomDNASequence(sequenceLength);
        vector<string> kmers = splitIntoKmers(sequence, k);
        dataset.push_back(pair<string, vector<string> >(sequence, kmers));
    }

    CascadeBloomfilter filter(filterSize, numHashes, k);
    for(size_t i = 0; i < dataset.size()/2; i++){
        // insert sequence into bloom filter
        filter.insert(dataset[i].first);
        // mark its k-mers as done and dusted
        for(const auto& kmer: dataset[i].second){
            kmers.insert(kmer);
            global_kmers.insert(kmer);
        }
    }

    double fp = 0;
    for(size_t i = dataset.size()/2; i < dataset.size(); i++){
        // It shouldn't, so if it does
        if(filter.contains(dataset[i].first)){
            // We check if its k-mers are inside the marked set
            for (const auto& kmer: dataset[i].second){
                if(kmers.find(kmer) == kmers.end()){
                    ++fp;
                    global_kmers.insert(kmer);
                }
            }
        }
    }

    // FPs in relation to kmers.
    cout << fp/global_kmers.size() << endl;

    return 0;
}

