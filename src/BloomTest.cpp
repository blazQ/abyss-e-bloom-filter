#include <cstddef>
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

    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " <seq_length> <k> <numSequences> <num_hashes>" << endl;
        return 1;
    }

    const size_t sequenceLength = atoi(argv[1]);
    const size_t k = atoi(argv[2]);

    if ( k < 3){
        cerr << "K must not be trvial!" << endl;
        return 0;
    }

    const size_t numSequences = atoi(argv[3]);
    const size_t numHashes = atoi(argv[4]);


    Bloomfilter<CityHash<string> >* cityFilter = new Bloomfilter<CityHash<string> >;
    Bloomfilter<MurmurHash3<string> >* murmurFilter = new Bloomfilter<MurmurHash3<string> >;
    Bloomfilter<NtHashFunction<string> >* ntFilter = new Bloomfilter<NtHashFunction<string> >(numHashes, k);

    unordered_set<string> sequences;
    size_t fpCity = 0;
    size_t totalCity = numSequences;

    for(size_t i=0; i<numSequences; i++){
        string sequence = generateRandomDNASequence(sequenceLength);

        if(i<numSequences/2){
            sequences.insert(sequence);
            cityFilter->insert(sequence);
        }

        else{
            if(cityFilter->contains(sequence)){
                if(sequences.find(sequence) == sequences.end())
                    fpCity++;
                else
                    totalCity--;
            }
        }
    }

    size_t fpMurmur=0;
    size_t totalMurmur = numSequences;
    for(size_t i=0; i<numSequences; i++){
        string sequence = generateRandomDNASequence(sequenceLength);

        if(i<numSequences/2){
            sequences.insert(sequence);
            murmurFilter->insert(sequence);
        }

        else{
            if(murmurFilter->contains(sequence)){
                if(sequences.find(sequence) == sequences.end())
                    fpMurmur++;
                else
                    totalMurmur--;
            }
        }
    }

    size_t fpNt = 0;
    size_t totalNt = numSequences;

    for(size_t i=0; i<numSequences; i++){
        string sequence = generateRandomDNASequence(sequenceLength);

        if(i<numSequences/2){
            sequences.insert(sequence);
            ntFilter->insert(sequence);
        }

        else{
            if(ntFilter->contains(sequence)){
                if(sequences.find(sequence) == sequences.end())
                    fpNt++;
                else
                    totalNt--;
            }
        }
    }

    cout << "CityHash, MurmurHash3, NtHash2" << endl;
    cout << fpCity/totalCity << "," << fpMurmur/totalMurmur << "," << fpNt/totalNt << endl;

    return 0;
}

