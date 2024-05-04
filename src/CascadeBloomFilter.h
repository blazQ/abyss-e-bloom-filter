#ifndef CASCADEBLOOMFILTER_H
#define CASCADEBLOOMFILTER_H

#include <iostream>
#include <nthash/nthash.hpp>
#include <bitset>
#include <memory>
#include <stdexcept>

using namespace std;

class CascadeBloomfilter
{
public:
	CascadeBloomfilter(size_t filter_size, size_t hash_func_count = 4, size_t k_size = 3)
	: hash_function_count(hash_func_count),
	  bloomfilter_stores(hash_func_count, vector<bool>(filter_size)),
	  object_count_(0),
      k(k_size)
	{
		if(0 == hash_func_count)
		{
			throw std::invalid_argument("Bloomfilter could not be initialized: hash_func_count must be larger than 0");
		}
        if(3 > k)
            throw std::invalid_argument("Bloomfilter could not be initalized: k value must be larger than 2");
	}


	void insert(const std::string& object)
	{
        nthash::NtHash nth(object, hash_function_count, k);
		/** WATCH OUT: Since nthash functions by hashing k-mer by k-mer, here i'm not inserting the sequence in the bloom filter. I'm inserting the k-mers of the sequence!*/
        while (nth.roll()) {
            for(size_t i = 0; i < hash_function_count; i++){
                const size_t index_to_set = nth.hashes()[i] % bloomfilter_stores[i].size();
                bloomfilter_stores[i][index_to_set] = true;
            }
        }
		++object_count_;
	}

	void clear()
	{
        for (auto& bitset : bloomfilter_stores) {
            bitset.clear(); // Reset each bitset in the vector
        }
        object_count_ = 0; // Reset the object count
	}

	bool contains(const std::string& object) const
	{
        nthash::NtHash nth(object, hash_function_count, k);
        while (nth.roll()) {
            for(size_t i = 0; i < hash_function_count; i++){
                const size_t index_to_get = nth.hashes()[i] % bloomfilter_stores[i].size();
                if(!bloomfilter_stores[i][index_to_get]) return false;
            }
        }
        return true;
	}

	size_t object_count() const
	{
		return object_count_;
	}

	bool empty() const
	{
		return 0 == object_count();
	}

	size_t size() const
	{
		return bloomfilter_stores[0].size();
	}

	size_t cascade_size() const
	{
		return bloomfilter_stores.size();
	}

private:

	const size_t hash_function_count;
	// Dynamically allocated vector of vector of bools.
    std::vector<std::vector<bool>> bloomfilter_stores;

	size_t object_count_;
    size_t k;

};

#endif // BLOOMFILTER_H
