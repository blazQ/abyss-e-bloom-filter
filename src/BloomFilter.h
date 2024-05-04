#include <cstddef>
#include <string>
#include <cstdint>
#include <bitset>
#include <stdexcept>
#include "city.h"
#include "MurmurHash3.h"
#include <iostream>
#include <nthash/nthash.hpp>

template<typename T>
class HashFunction {
public:
    virtual size_t operator()(const T& data, size_t length) const = 0;
};

template<typename T>
class MurmurHash3 : public HashFunction<T> {
public:
    size_t operator()(const T& data, size_t length) const override{
        uint32_t hashValue;
        const void* keyPtr = static_cast<const void*>(data.c_str());
        MurmurHash3_x86_32(keyPtr, length, 0, &hashValue);
        return hashValue;
    }
};

template<typename T>
class CityHash : public HashFunction<T> {
public:
    size_t operator()(const T& data, size_t length) const override{
        return CityHash64(data.c_str(), length);
    }
};

template<typename T>
class NtHashFunction : public HashFunction<T> {

public:
    NtHashFunction(size_t hashes, size_t k) :
        num_hashes(hashes),
        k(k)
    {}

    size_t operator()(const T& data, size_t length) const override {
        nthash::NtHash nth(data, num_hashes, k);
        while(nth.roll()){}
        return nth.get_forward_hash();
    }

private:
    size_t num_hashes;
    size_t k;
};

template <typename T>
struct HashFunctionTraits {
    using ConstructorType = void;
};

template <>
struct HashFunctionTraits<NtHashFunction<std::string>> {
    using ConstructorType = NtHashFunction<std::string>;
};

template <>
struct HashFunctionTraits<MurmurHash3<std::string>> {
    using ConstructorType = MurmurHash3<std::string>;
};

template <>
struct HashFunctionTraits<CityHash<std::string>> {
    using ConstructorType = CityHash<std::string>;
};

// Defining a generic HashFunction type and a generic Size value for bitset instantiation.
// You can do it differently if you prefer, for example by using a boolean vector and resizing with a constructor argument.
// A bitset should have less memory overhead (in theory)
template <typename HashFunc>
class Bloomfilter
{
public:
    Bloomfilter(size_t filter_size = default_size) :
        bloomfilter_store(filter_size),
        object_count_(0),
        hashFunc()
    {
        using ConstructorType = typename HashFunctionTraits<HashFunc>::ConstructorType;
        hashFunc = ConstructorType();
    }

    Bloomfilter(size_t filter_size, size_t hashes, size_t k) :
        bloomfilter_store(filter_size),
        object_count_(0),
        hashFunc(hashes, k)
    {
        using ConstructorType = typename HashFunctionTraits<HashFunc>::ConstructorType;
        hashFunc = ConstructorType(hashes, k);
    }

    void insert(const std::string& object)
    {
        size_t hash = hashFunc(object, object.size()) % bloomfilter_store.size();
        bloomfilter_store[hash] = true;
        ++object_count_;
    }

    void clear()
    {
        bloomfilter_store.clear();
        object_count_ = 0; // Reset the object count
    }

    bool contains(const std::string& object) const
    {
        size_t hash = hashFunc(object, object.size()) % bloomfilter_store.size();
        return bloomfilter_store[hash];
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
        return bloomfilter_store.size();
    }

private:

    static constexpr size_t default_size = 33554432;

    std::vector<bool> bloomfilter_store;

    size_t object_count_;

    HashFunc hashFunc;
};
