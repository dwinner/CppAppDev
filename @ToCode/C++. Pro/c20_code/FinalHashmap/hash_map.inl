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




	// Dereferencing or incrementing an iterator constructed with the default
	// ctor is undefined, so it doesn't matter what values we give here.
	template<typename HashMap>
	const_hash_map_iterator<HashMap>::const_hash_map_iterator()
		: mBucketIndex(0), mListIterator(list_iterator_type()), mHashmap(nullptr)
	{
	}

	template<typename HashMap>
	const_hash_map_iterator<HashMap>::const_hash_map_iterator(size_t bucket, list_iterator_type listIt, const HashMap* inHashmap)
		: mBucketIndex(bucket), mListIterator(listIt), mHashmap(inHashmap)
	{
	}

	// Return the actual element
	template<typename HashMap>
	const typename const_hash_map_iterator<HashMap>::value_type& const_hash_map_iterator<HashMap>::operator*() const
	{
		return *mListIterator;
	}

	// Return the iterator, so the compiler can apply -> to it to access
	// the actual desired field.
	template<typename HashMap>
	const typename const_hash_map_iterator<HashMap>::value_type* const_hash_map_iterator<HashMap>::operator->() const
	{
		return &(*mListIterator);
	}

	// Defer the details to the increment() helper.
	template<typename HashMap>
	const_hash_map_iterator<HashMap>& const_hash_map_iterator<HashMap>::operator++()
	{
		increment();
		return *this;
	}

	// Defer the details to the increment() helper.
	template<typename HashMap>
	const_hash_map_iterator<HashMap> const_hash_map_iterator<HashMap>::operator++(int)
	{
		auto oldIt = *this;
		increment();
		return oldIt;
	}

	// Defer the details to the decrement() helper.
	template<typename HashMap>
	const_hash_map_iterator<HashMap>& const_hash_map_iterator<HashMap>::operator--()
	{
		decrement();
		return *this;
	}

	// Defer the details to the decrement() helper.
	template<typename HashMap>
	const_hash_map_iterator<HashMap> const_hash_map_iterator<HashMap>::operator--(int)
	{
		auto oldIt = *this;
		decrement();
		return oldIt;
	}

	template<typename HashMap>
	bool const_hash_map_iterator<HashMap>::operator==(const const_hash_map_iterator<HashMap>& rhs) const
	{
		// All fields, including the hash_map to which the iterators refer,
		// must be equal.
		return (mHashmap == rhs.mHashmap && mBucketIndex == rhs.mBucketIndex && mListIterator == rhs.mListIterator);
	}

	template<typename HashMap>
	bool const_hash_map_iterator<HashMap>::operator!=(const const_hash_map_iterator<HashMap>& rhs) const
	{
		return !(*this == rhs);
	}

	// Behavior is undefined if mListIterator already refers to the past-the-end
	// element, or is otherwise invalid.
	template<typename HashMap>
	void const_hash_map_iterator<HashMap>::increment()
	{
		// mListIterator is an iterator into a single bucket. Increment it.
		++mListIterator;

		// If we're at the end of the current bucket,
		// find the next bucket with elements.
		auto& buckets = mHashmap->mBuckets;
		if (mListIterator == ::end(buckets[mBucketIndex])) {
			for (size_t i = mBucketIndex + 1; i < buckets.size(); i++) {
				if (!buckets[i].empty()) {
					// We found a non-empty bucket.
					// Make mListIterator refer to the first element in it.
					mListIterator = ::begin(buckets[i]);
					mBucketIndex = i;
					return;
				}
			}
			// No more empty buckets. Assign mListIterator to refer to the end
			// iterator of the last list.
			mBucketIndex = buckets.size() - 1;
			mListIterator = ::end(buckets[mBucketIndex]);
		}
	}

	// Behavior is undefined if mListIterator already refers to the first element,
	// or is otherwise invalid.
	template<typename HashMap>
	void const_hash_map_iterator<HashMap>::decrement()
	{
		// mListIterator is an iterator into a single bucket.
		// If it's at the beginning of the current bucket, don't decrement it.
		// Instead, try to find a non-empty bucket before the current one.
		auto& buckets = mHashmap->mBuckets;
		if (mListIterator == ::begin(buckets[mBucketIndex])) {
			for (int i = mBucketIndex - 1; i >= 0; --i) {
				if (!buckets[i].empty()) {
					mListIterator = ::end(buckets[i]);
					--mListIterator;
					mBucketIndex = i;
					return;
				}
			}
			// No more non-empty buckets. This is an invalid decrement.
			// Assign mListIterator to refer to the end iterator of the last list.
			mBucketIndex = buckets.size() - 1;
			mListIterator = ::end(buckets[mBucketIndex]);
		} else {
			// We're not at the beginning of the bucket, so just move down.
			--mListIterator;
		}
	}




	template<typename HashMap>
	hash_map_iterator<HashMap>::hash_map_iterator() : const_hash_map_iterator()
	{
	}

	template<typename HashMap>
	hash_map_iterator<HashMap>::hash_map_iterator(size_t bucket, list_iterator_type listIt, HashMap* inHashmap)
		: const_hash_map_iterator(bucket, listIt, inHashmap)
	{
	}

	// Return the actual element.
	template<typename HashMap>
	typename hash_map_iterator<HashMap>::value_type& hash_map_iterator<HashMap>::operator*()
	{
		return const_cast<value_type&>(*mListIterator);
	}

	// Return the iterator, so the compiler can apply -> to it to access
	// the actual desired field.
	template<typename HashMap>
	typename hash_map_iterator<HashMap>::value_type* hash_map_iterator<HashMap>::operator->()
	{
		return const_cast<value_type*>(&(*mListIterator));
	}

	// Defer the details to the increment() helper in the base class.
	template<typename HashMap>
	hash_map_iterator<HashMap>& hash_map_iterator<HashMap>::operator++()
	{
		increment();
		return *this;
	}

	// Defer the details to the increment() helper in the base class.
	template<typename HashMap>
	hash_map_iterator<HashMap> hash_map_iterator<HashMap>::operator++(int)
	{
		auto oldIt = *this;
		increment();
		return oldIt;
	}

	// Defer the details to the decrement() helper in the base class.
	template<typename HashMap>
	hash_map_iterator<HashMap>& hash_map_iterator<HashMap>::operator--()
	{
		decrement();
		return *this;
	}

	// Defer the details to the decrement() helper in the base class.
	template<typename HashMap>
	hash_map_iterator<HashMap> hash_map_iterator<HashMap>::operator--(int)
	{
		auto oldIt = *this;
		decrement();
		return oldIt;
	}




	// Resize mBuckets with the number of buckets.
	template <typename Key, typename T, typename Compare, typename Hash>
	hash_map<Key, T, Compare, Hash>::hash_map(const Compare& comp, size_type numBuckets, const Hash& hash)
		: mSize(0), mComp(comp), mHash(hash)
	{
		if (numBuckets == 0) {
			throw std::invalid_argument("Number of buckets must be positive");
		}
		mBuckets.resize(numBuckets);
	}

	// Make a call to insert() to actually insert the elements.
	template <typename Key, typename T, typename Compare, typename Hash>
	template <typename InputIterator>
	hash_map<Key, T, Compare, Hash>::hash_map(InputIterator first, InputIterator last, const Compare& comp, size_type numBuckets, const Hash& hash)
		: mSize(0), mComp(comp), mHash(hash)
	{
		if (numBuckets == 0) {
			throw std::invalid_argument("Number of buckets must be positive");
		}
		mBuckets.resize(numBuckets);
		insert(first, last);
	}

	// Initializer list constructor
	template <typename Key, typename T, typename Compare, typename Hash>
	hash_map<Key, T, Compare, Hash>::hash_map(std::initializer_list<value_type> il, const Compare& comp, size_type numBuckets, const Hash& hash)
		: mSize(0), mComp(comp), mHash(hash)
	{
		if (numBuckets == 0) {
			throw std::invalid_argument("Number of buckets must be positive");
		}
		mBuckets.resize(numBuckets);
		insert(::begin(il), ::end(il));
	}

	// Initializer list assignment operator
	template <typename Key, typename T, typename Compare, typename Hash>
	hash_map<Key, T, Compare, Hash>& hash_map<Key, T, Compare, Hash>::operator=(std::initializer_list<value_type> il)
	{
		clear();
		insert(::begin(il), ::end(il));
		return *this;
	}
	
	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::ListType::iterator hash_map<Key, T, Compare, Hash>::findElement(const key_type& x, size_type& bucket)
	{
		// hash the key to get the bucket
		bucket = mHash(x) % mBuckets.size();

		// Look for the key in the bucket
		for (auto it = ::begin(mBuckets[bucket]); it != ::end(mBuckets[bucket]); ++it) {
			if (mComp(it->first, x)) {
				return it;
			}
		}
		return ::end(mBuckets[bucket]);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator hash_map<Key, T, Compare, Hash>::find(const key_type& x)
	{
		size_t bucket;
		// Use the findElement() helper.
		auto it = findElement(x, bucket);
		if (it == ::end(mBuckets[bucket])) {
			// Element not found -- return the end iterator.
			return end();
		}
		// Element found -- convert the bucket/iterator to a hash_map_iterator.
		return hash_map_iterator<hash_map_type>(bucket, it, this);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::const_iterator hash_map<Key, T, Compare, Hash>::find(const key_type& x) const
	{
		size_t bucket;
		// Use the findElement() helper.
		// Use const_cast to avoid having to duplicate findElement().
		auto it = const_cast<hash_map_type*>(this)->findElement(x, bucket);
		if (it == ::end(mBuckets[bucket])) {
			// Element not found -- return the end iterator.
			return end();
		}
		// Element found -- convert the bucket/iterator to a const_hash_map_iterator.
		return const_hash_map_iterator<hash_map_type>(bucket, it, this);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	std::pair<typename hash_map<Key, T, Compare, Hash>::iterator, typename hash_map<Key, T, Compare, Hash>::iterator>
		hash_map<Key, T, Compare, Hash>::equal_range(const key_type& x)
	{
		auto it = find(x);
		return std::make_pair(it, it);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	std::pair<typename hash_map<Key, T, Compare, Hash>::const_iterator, typename hash_map<Key, T, Compare, Hash>::const_iterator>
		hash_map<Key, T, Compare, Hash>::equal_range(const key_type& x) const
	{
		auto it = find(x);
		return std::make_pair(it, it);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::size_type hash_map<Key, T, Compare, Hash>::count(const key_type& x) const
	{
		// There are either 1 or 0 elements matching key x.
		// If we can find a match, return 1, otherwise return 0.
		if (find(x) == end()) {
			return 0;
		} else {
			return 1;
		}
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	T& hash_map<Key, T, Compare, Hash>::operator[] (const key_type& x)
	{
		// This definition is the same as that used by map, according to
		// the standard.
		// It's a bit cryptic, but it basically attempts to insert
		// a new key/value pair of x and a new value. Regardless of whether
		// the insert succeeds or fails, insert() returns a pair of an
		// iterator/bool. The iterator refers to a key/value pair, the
		// second element of which is the value we want to return.
		return ((insert(std::make_pair(x, T()))).first)->second;
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	std::pair<typename hash_map<Key, T, Compare, Hash>::iterator, bool> hash_map<Key, T, Compare, Hash>::insert(const value_type& x)
	{
		size_t bucket;
		// Try to find the element.
		auto it = findElement(x.first, bucket);
		bool inserted = false;
		if (it == ::end(mBuckets[bucket])) {
			// We didn't find the element, so insert a new one.
			it = mBuckets[bucket].insert(::end(mBuckets[bucket]), x);
			inserted = true;
			mSize++;
		}
		return std::make_pair(hash_map_iterator<hash_map_type>(bucket, it, this), inserted);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator
		hash_map<Key, T, Compare, Hash>::insert(iterator position, const value_type& x)
	{
		// Completely ignore position.
		return insert(x).first;
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	template <typename InputIterator>
	void hash_map<Key, T, Compare, Hash>::insert(InputIterator first, InputIterator last)
	{
		// Copy each element in the range by using an insert_iterator adapter.
		// Give begin() as a dummy position -- insert ignores it anyway.
		std::insert_iterator<hash_map_type> inserter(*this, begin());
		std::copy(first, last, inserter);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	void hash_map<Key, T, Compare, Hash>::insert(std::initializer_list<value_type> il)
	{
		insert(::begin(il), ::end(il));
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	std::pair<typename hash_map<Key, T, Compare, Hash>::iterator, bool> hash_map<Key, T, Compare, Hash>::emplace(value_type&& x)
	{
		size_t bucket;
		// Try to find the element.
		auto it = findElement(x.first, bucket);
		bool inserted = false;
		if (it == ::end(mBuckets[bucket])) {
			// We didn't find the element, so emplace a new one.
			it = mBuckets[bucket].emplace(::end(mBuckets[bucket]), x);
			inserted = true;
			mSize++;
		}
		return std::make_pair(hash_map_iterator<hash_map_type>(bucket, it, this), inserted);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator
		hash_map<Key, T, Compare, Hash>::emplace_hint(iterator hint, value_type&& x)
	{
		// Completely ignore hint.
		return emplace(std::forward<value_type>(x)).first;
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::size_type hash_map<Key, T, Compare, Hash>::erase(const key_type& x)
	{
		size_t bucket;

		// First, try to find the element.
		auto it = findElement(x, bucket);

		if (it != ::end(mBuckets[bucket])) {
			// The element exists -- erase it.
			mBuckets[bucket].erase(it);
			mSize--;
			return 1;
		} else {
			return 0;
		}
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator hash_map<Key, T, Compare, Hash>::erase(iterator position)
	{
		iterator next = position;
		++next;

		// Erase the element from its bucket.
		mBuckets[position.mBucketIndex].erase(position.mListIterator);
		mSize--;

		return next;
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator hash_map<Key, T, Compare, Hash>::erase(iterator first, iterator last)
	{
		// Erase all the elements in the range.
		for (iterator next = first; next != last;) {
			next = erase(next);
		}

		return last;
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	void hash_map<Key, T, Compare, Hash>::clear() noexcept
	{
		// Call clear on each bucket.
		for (auto& bucket : mBuckets) {
			bucket.clear();
		}
		mSize = 0;
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	bool hash_map<Key, T, Compare, Hash>::empty() const
	{
		return mSize == 0;
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::size_type hash_map<Key, T, Compare, Hash>::size() const
	{
		return mSize;
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::size_type hash_map<Key, T, Compare, Hash>::max_size() const
	{
		// In the worst case, all the elements hash to the same
		// list, so the max_size is the max_size of a single list.
		// This code assumes that all the lists have the same max_size.
		return mBuckets[0].max_size();
	}

	// Just swap the four data members. Use the generic swap template.
	template <typename Key, typename T, typename Compare, typename Hash>
	void hash_map<Key, T, Compare, Hash>::swap(hash_map_type& hashIn)
	{
		// Explicitly qualify with std:: so the compiler doesn't think
		// it's a recursive call.
		std::swap(*this, hashIn);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator hash_map<Key, T, Compare, Hash>::begin()
	{
		if (mSize == 0) {
			// Special case: there are no elements, so return the end iterator.
			return end();
		}

		// We know there is at least one element. Find the first element.
		for (size_t i = 0; i < mBuckets.size(); ++i) {
			if (!mBuckets[i].empty()) {
				return hash_map_iterator<hash_map_type>(i, ::begin(mBuckets[i]), this);
			}
		}
		// Should never reach here, but if we do, return the end iterator.
		return end();
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::const_iterator hash_map<Key, T, Compare, Hash>::begin() const
	{
		// Use const_cast to call the non-const version of begin(). That
		// one returns an iterator which is convertible to a const_iterator.
		return const_cast<hash_map_type*>(this)->begin();
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::const_iterator hash_map<Key, T, Compare, Hash>::cbegin() const
	{
		return begin();
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::iterator hash_map<Key, T, Compare, Hash>::end()
	{
		// The end iterator is the end iterator of the list of the last bucket.
		size_t bucket = mBuckets.size() - 1;
		return hash_map_iterator<hash_map_type>(bucket, ::end(mBuckets[bucket]), this);
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::const_iterator hash_map<Key, T, Compare, Hash>::end() const
	{
		// Use const_cast to call the non-const version of end(). That
		// one returns an iterator which is convertible to a const_iterator.
		return const_cast<hash_map_type*>(this)->end();
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::const_iterator hash_map<Key, T, Compare, Hash>::cend() const
	{
		return end();
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::key_compare hash_map<Key, T, Compare, Hash>::key_comp() const
	{
		return mComp;
	}

	template <typename Key, typename T, typename Compare, typename Hash>
	typename hash_map<Key, T, Compare, Hash>::value_compare hash_map<Key, T, Compare, Hash>::value_comp() const
	{
		return value_compare(mComp);
	}

}