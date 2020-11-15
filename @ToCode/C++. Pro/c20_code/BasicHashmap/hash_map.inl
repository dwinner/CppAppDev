#include <stdexcept>
#include <algorithm>
#include <functional>

namespace ProCpp {

	// Calculate a hash by treating the key as a sequence
	// of bytes and summing the ASCII values of the bytes.
	template <typename T>
	size_t hash<T>::operator()(const T& key) const
	{
		size_t bytes = sizeof(key);
		size_t res = 0;
		for (size_t i = 0; i < bytes; ++i) {
			unsigned char b = *((unsigned char*)&key + i);
			res += b;
		}
		return res;
	}




	// Calculate a hash by summing the ASCII values of all characters.
	size_t hash<std::string>::operator()(const std::string& key) const
	{
		size_t sum = 0;
		for (size_t i = 0; i < key.size(); ++i) {
			sum += (unsigned char)key[i];
		}
		return sum;
	}




	// Resize mBuckets with the number of buckets.
	template <typename Key, typename T, typename Compare, typename Hash>
	hash_map<Key, T, Compare, Hash>::hash_map(const Compare& comp, size_t numBuckets, const Hash& hash)
		: mSize(0), mComp(comp), mHash(hash)
	{
		if (numBuckets == 0) {
			throw std::invalid_argument("Number of buckets must be positive");
		}
		mBuckets.resize(numBuckets);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::ListType::iterator hash_map<Key, T, Compare, Hash>::findElement(const key_type& k, size_t& bucket)
	{
		// Hash the key to get the bucket.
		bucket = mHash(k) % mBuckets.size();

		// Look for the key in the bucket.
		for (auto it = ::begin(mBuckets[bucket]); it != ::end(mBuckets[bucket]); ++it) {
			if (mComp(it->first, k)) {
				return it;
			}
		}
		return ::end(mBuckets[bucket]);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::value_type* hash_map<Key, T, Compare, Hash>::find(const key_type& k)
	{
		size_t bucket;
		// Use the findElement() helper.
		auto it = findElement(k, bucket);
		if (it == ::end(mBuckets[bucket])) {
			// Element not found -- return nullptr.
			return nullptr;
		}
		// Element found -- return a pointer to it.
		return &(*it);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	const typename hash_map<Key, T, Compare, Hash>::value_type* hash_map<Key, T, Compare, Hash>::find(const key_type& k) const
	{
		return const_cast<hash_map<Key, T, Compare, Hash>*>(this)->find(k);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	T& hash_map<Key, T, Compare, Hash>::operator[] (const key_type& k)
	{
		// Try to find the element. If it doesn't exist, add a new element.
		value_type* found = find(k);
		if (found == nullptr) {
			insert(std::make_pair(k, T()));
			found = find(k);
		}
		return found->second;
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	void hash_map<Key, T, Compare, Hash>::insert(const value_type& x)
	{
		size_t bucket;

		// Try to find the element.
		auto it = findElement(x.first, bucket);

		if (it != ::end(mBuckets[bucket])) {
			// The element already exists.
			return;
		} else {
			// We didn't find the element, so insert a new one.
			mSize++;
			mBuckets[bucket].push_back(x);
		}
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	void hash_map<Key, T, Compare, Hash>::erase(const key_type& k)
	{
		size_t bucket;

		// First, try to find the element.
		auto it = findElement(k, bucket);

		if (it != ::end(mBuckets[bucket])) {
			// The element exists -- erase it.
			mBuckets[bucket].erase(it);
			mSize--;
		}
	}

}