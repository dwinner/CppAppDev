#pragma once

#include <cstddef>
#include <queue>
#include <stdexcept>
#include <memory>

// Provides an object pool that can be used with any class that provides a
// default constructor.
//
// The object pool constructor creates a pool of objects, which it hands out
// to clients when requested via the acquireObject() method. acquireObject()
// returns an Object which is a std::shared_ptr with a custom deleter that
// automatically puts the object back into the object pool when the shared_ptr
// is destroyed and its reference reaches 0.
//
// The constructor and destructor on each object in the pool will be called only
// once each for the lifetime of the program, not once per acquisition and release.
//
// The primary use of an object pool is to avoid creating and deleting objects
// repeatedly. The object pool is most suited to applications that use large 
// numbers of objects with expensive constructors for short periods of time, if
// a profiler tells you that allocating and deallocating these objects is a
// bottleneck.
template <typename T>
class ObjectPool
{
public:
	// Creates an object pool with chunkSize objects.
	// Whenever the object pool runs out of objects, chunkSize
	// more objects will be added to the pool. The pool only grows:
	// objects are never removed from the pool (freed), until
	// the pool is destroyed.
	//
	// Throws invalid_argument if chunkSize is 0.
	// Throws bad_alloc if allocation fails.
	ObjectPool(size_t chunkSize = kDefaultChunkSize);

	// Prevent assignment and pass-by-value
	ObjectPool(const ObjectPool<T>& src) = delete;
	ObjectPool<T>& operator=(const ObjectPool<T>& rhs) = delete;

	// The type of smart pointer returned by acquireObject().
	using Object = std::shared_ptr<T>;

	// Reserves an object for use.
	Object acquireObject();

private:
	// mFreeList stores the objects that are not currently in use by clients.
	std::queue<std::unique_ptr<T>> mFreeList;

	size_t mChunkSize;
	static const size_t kDefaultChunkSize = 10;

	// Allocates mChunkSize new objects and adds them to mFreeList.
	void allocateChunk();
};

template<typename T>
const size_t ObjectPool<T>::kDefaultChunkSize;

template <typename T>
ObjectPool<T>::ObjectPool(size_t chunkSize)
{
	if (chunkSize == 0) {
		throw std::invalid_argument("chunk size must be positive");
	}
	mChunkSize = chunkSize;
	// Create mChunkSize objects to start.
	allocateChunk();
}

// Allocates mChunkSize new objects.
template <typename T>
void ObjectPool<T>::allocateChunk()
{
	for (size_t i = 0; i < mChunkSize; ++i) {
		mFreeList.emplace(std::make_unique<T>());
	}
}

template <typename T>
typename ObjectPool<T>::Object ObjectPool<T>::acquireObject()
{
	if (mFreeList.empty()) {
		allocateChunk();
	}

	// Move next free object from the queue to a local unique_ptr.
	std::unique_ptr<T> obj(std::move(mFreeList.front()));
	mFreeList.pop();

	// Convert the object pointer to an Object (a shared_ptr with
	// a custom deleter).
	Object smartObject(obj.release(), [this](T* t){
		// The custom deleter doesn't actually deallocate the
		// memory, but simply puts the object back on the free list.
		mFreeList.push(std::unique_ptr<T>(t));
	});

	// Return the Object.
	return smartObject;
}
