#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <nthash/nthash.hpp>
#include <bitset>
#include <memory>
#include <stdexcept>

class Bloomfilter
{
public:
	Bloomfilter(size_t hash_func_count = 4, size_t k_size = 3)
	: hash_function_count(hash_func_count),
	  bloomfilter_stores(hash_func_count, std::bitset<bloomfilter_store_size>()),
	  object_count_(0),
      k(k_size)
	{
		if(0 == hash_func_count)
		{
			throw std::invalid_argument("Bloomfilter could not be initialized: hash_func_count must be larger than 0");
		}
        if(3 > k)
            throw std::invalid_argument("Bloomfilter could not be initilized: k value must be larger than 2");
	}


	void insert(const std::string& object)
	{
        nthash::NtHash nth(object, hash_function_count, k);
		/** WATCH OUT: Since nthash functions by hashing k-mer by k-mer, here i'm not inserting the sequence in the bloom filter. I'm inserting the k-mers of the sequence!*/
        while (nth.roll()) {
            for(size_t i = 0; i < hash_function_count; i++){
                const size_t index_to_set = nth.hashes()[i] % bloomfilter_store_size;
                bloomfilter_stores[i][index_to_set] = true;
            }
        }
		++object_count_;
	}

	void clear()
	{
        for (auto& bitset : bloomfilter_stores) {
            bitset.reset(); // Reset each bitset in the vector
        }
        object_count_ = 0; // Reset the object count
	}

	bool contains(const std::string& object) const
	{
        nthash::NtHash nth(object, hash_function_count, k);
        while (nth.roll()) {
            for(size_t i = 0; i < hash_function_count; i++){
                const size_t index_to_get = nth.hashes()[i] % bloomfilter_store_size;
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

private:
	// Size of the bloom filter state in bits (2^25).
	static constexpr size_t bloomfilter_store_size = 33554432;

	const size_t hash_function_count;

    // Statically declared array of bitsets, one for each hash function.
    std::vector<std::bitset<bloomfilter_store_size>> bloomfilter_stores;

	size_t object_count_;
    size_t k;

};

#endif // BLOOMFILTER_H
