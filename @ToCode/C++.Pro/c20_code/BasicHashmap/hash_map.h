#pragma once

#include <cstddef>
#include <vector>
#include <list>
#include <string>

namespace ProCpp {

	// A default hash object
	template <typename T>
	class hash
	{
	public:
		size_t operator()(const T& key) const;
	};

	// A hash specialization for strings
	template <>
	class hash<std::string>
	{
	public:
		size_t operator()(const std::string& key) const;
	};




	template <typename Key, typename T, typename Compare = std::equal_to<Key>, typename Hash = hash<Key>>
	class hash_map
	{
	public:
		using key_type = Key;
		using mapped_type = T;
		using value_type = std::pair<const Key, T>;

		// Throws invalid_argument if the number of buckets is illegal.
		explicit hash_map(const Compare& comp = Compare(), size_t numBuckets = 101, const Hash& hash = Hash());

		// Inserts the key/value pair x.
		void insert(const value_type& x);

		// Removes the element with key k, if it exists.
		void erase(const key_type& k);

		// Find returns a pointer to the element with key k.
		// Returns nullptr if no element with that key exists.
		value_type* find(const key_type& k);
		const value_type* find(const key_type& k) const;

		// operator[] finds the element with key k or inserts an
		// element with that key if none exists yet. Returns a reference to
		// the value corresponding to that key.
		T& operator[] (const key_type& k);

	private:
		using ListType = std::list<value_type>;

		typename ListType::iterator findElement(const key_type& k, size_t& bucket);

		std::vector<ListType> mBuckets;
		size_t mSize;
		Compare mComp;
		Hash mHash;
	};

}

#include "hash_map.inl"
