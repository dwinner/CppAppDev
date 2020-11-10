#pragma once

#include <cstddef>
#include <vector>
#include <list>
#include <iterator> 
#include <string>
#include <initializer_list>

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




	// const_hash_map_iterator class definition
	template <typename HashMap>
	class const_hash_map_iterator : public std::iterator<std::bidirectional_iterator_tag, typename HashMap::value_type>
	{
		// The hash_map class needs access to all members of the const_hash_map_iterator
		friend HashMap;

	public:
		using list_iterator_type = typename HashMap::ListType::const_iterator;

		const_hash_map_iterator(); // Bidirectional iterators must supply default ctor
		const_hash_map_iterator(size_t bucket, list_iterator_type listIt, const HashMap* inHashmap);

		const value_type& operator*() const;

		// Return type must be something to which -> can be applied.
		// Return a pointer to a pair<const Key, T>, to which the compiler will
		// apply -> again.
		const value_type* operator->() const;

		const_hash_map_iterator<HashMap>& operator++();
		const_hash_map_iterator<HashMap> operator++(int);

		const_hash_map_iterator<HashMap>& operator--();
		const_hash_map_iterator<HashMap> operator--(int);

		// Don't need to define a copy constructor or operator= because the
		// default behavior is what we want.

		// Don't need destructor because the default behavior
		// (not deleting mHashmap) is what we want.

		// The following are ok as member functions because we don't
		// support comparisons of different types to this one.
		bool operator==(const const_hash_map_iterator<HashMap>& rhs) const;
		bool operator!=(const const_hash_map_iterator<HashMap>& rhs) const;

	protected:
		size_t mBucketIndex;
		list_iterator_type mListIterator;
		const HashMap* mHashmap;

		// Helper methods for operator++ and operator--
		void increment();
		void decrement();
	};

	template <typename HashMap>
	class hash_map_iterator : public const_hash_map_iterator<HashMap>
	{
		// The hash_map class needs access to all members of the hash_map_iterator
		friend HashMap;

	public:
		using list_iterator_type = typename HashMap::ListType::iterator;

		hash_map_iterator(); // Bidirectional iterators must supply default ctor
		hash_map_iterator(size_t bucket, list_iterator_type listIt, HashMap* inHashmap);
		
		value_type& operator*();

		// Return type must be something to which -> can be applied.
		// Return a pointer to a pair<const Key, T>, to which the compiler will
		// apply -> again.
		value_type* operator->();

		hash_map_iterator<HashMap>& operator++();
		hash_map_iterator<HashMap> operator++(int);

		hash_map_iterator<HashMap>& operator--();
		hash_map_iterator<HashMap> operator--(int);
	};




	template <typename Key, typename T, typename Compare = std::equal_to<Key>, typename Hash = hash<Key>>
	class hash_map
	{
	public:
		using key_type = Key;
		using mapped_type = T;
		using value_type = std::pair<const Key, T>;
		using key_compare = Compare;
		using reference = std::pair<const Key, T>&;
		using const_reference = const std::pair<const Key, T>&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using hash_map_type = hash_map<Key, T, Compare, Hash>;
		using iterator = hash_map_iterator<hash_map_type>;
		using const_iterator = const_hash_map_iterator<hash_map_type>;

		// Required class definition for associative containers
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class hash_map_type;

		public:
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}

		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) { }
		};

		// The iterator classes need access to all members of the hash_map
		friend class hash_map_iterator<hash_map_type>;
		friend class const_hash_map_iterator<hash_map_type>;

		// Throws invalid_argument if the number of buckets is illegal.
		explicit hash_map(const Compare& comp = Compare(), size_type numBuckets = 101, const Hash& hash = Hash());

		// Throws invalid_argument if the number of buckets is illegal.
		template <typename InputIterator>
		hash_map(InputIterator first, InputIterator last, const Compare& comp = Compare(),
			size_type numBuckets = 101, const Hash& hash = Hash());

		// Initializer list constructor
		// Throws invalid_argument if the number of buckets is illegal. 
		explicit hash_map(std::initializer_list<value_type> il, const Compare& comp = Compare(), size_type numBuckets = 101,
			const Hash& hash = Hash());

		// Initializer list assignment operator
		hash_map_type& operator=(std::initializer_list<value_type> il);

		// Iterator methods
		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;

		// Size methods
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		// Element insert methods
		T& operator[] (const key_type& x);
		std::pair<iterator, bool> insert(const value_type& x);
		iterator insert(iterator position, const value_type& x);
		template <typename InputIterator>
		void insert(InputIterator first, InputIterator last);
		void insert(std::initializer_list<value_type> il);

		// Emplace methods
		std::pair<iterator, bool> emplace(value_type&& x);
		iterator emplace_hint(iterator hint, value_type&& x);

		// Element delete methods
		size_type erase(const key_type& x);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		// Other modifying utilities
		void swap(hash_map_type& hashIn);
		void clear() noexcept;

		// Access methods for STL conformity
		key_compare key_comp() const;
		value_compare value_comp() const;

		// Lookup methods
		iterator find(const key_type& x);
		const_iterator find(const key_type& x) const;
		std::pair<iterator, iterator> equal_range(const key_type& x);
		std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const;

		size_type count(const key_type& x) const;

	private:
		using ListType = std::list<value_type>;

		typename ListType::iterator findElement(const key_type& x, size_type& bucket);

		std::vector<ListType> mBuckets;
		size_type mSize;
		Compare mComp;
		Hash mHash;
	};

}

#include "hash_map.inl"
