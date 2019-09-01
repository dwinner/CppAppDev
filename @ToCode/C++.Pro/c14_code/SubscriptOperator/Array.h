#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class Array
{
public:
	// Creates an array with a default size that will grow as needed.
	Array();
	virtual ~Array();

	// Disallow assignment and pass-by-value
	Array<T>& operator=(const Array<T>& rhs) = delete;
	Array(const Array<T>& src) = delete;

	T& operator[](size_t x);
	//const T& operator[](size_t x);  // Error! Can't overload based on return type.
	const T& operator[](size_t x) const;

	// Returns the value at index x. If index x does not exist in the array,
	// throws an exception of type out_of_range.
	T getElementAt(size_t x) const;
	// Sets the value at index x to val. If index x is out of range,
	// allocates more space to make it in range.
	void setElementAt(size_t x, const T& val);

private:
	static const size_t kAllocSize = 4;
	void resize(size_t newSize);
	// Sets all elements to 0
	void initializeElements();
	T* mElems;
	size_t mSize;
};

template <typename T>
Array<T>::Array()
{
	mSize = kAllocSize;
	mElems = new T[mSize];
	initializeElements();
}

template <typename T>
Array<T>::~Array()
{
	delete [] mElems;
	mElems = nullptr;
}

template <typename T>
void Array<T>::initializeElements()
{
	for (size_t i = 0; i < mSize; i++)
		mElems[i] = T();
}

template <typename T>
void Array<T>::resize(size_t newSize)
{
	// Make a copy of the current elements pointer and size
	T* oldElems = mElems;
	size_t oldSize = mSize;

	// Create new bigger array
	mSize = newSize;           // store the new size
	mElems = new T[newSize]; // Allocate the new array of the new size
	initializeElements();      // Initialize all elements to 0

	// The new size is always bigger than the old size
	for (size_t i = 0; i < oldSize; i++) {
		// Copy the elements from the old array to the new one
		mElems[i] = oldElems[i];
	}

	delete [] oldElems; // free the memory for the old array
}

template <typename T>
T& Array<T>::operator[](size_t x)
{
	if (x < 0) {
		throw std::out_of_range("");
	}
	if (x >= mSize) {
		// Allocate kAllocSize past the element the client wants
		resize(x + kAllocSize);
	}
	return mElems[x];
}

template <typename T>
const T& Array<T>::operator[](size_t x) const
{
	if (x < 0 || x >= mSize) {
		throw std::out_of_range("");
	}
	return mElems[x];
}

template <typename T>
T Array<T>::getElementAt(size_t x) const
{
	if (x < 0 || x >= mSize) {
		throw std::out_of_range("");
	}
	return mElems[x];
}

template <typename T>
void Array<T>::setElementAt(size_t x, const T& val)
{
	if (x < 0) {
		throw std::out_of_range("");
	}
	if (x >= mSize) {
		// Allocate kAllocSize past the element the client wants
		resize(x + kAllocSize);
	}
	mElems[x] = val;
}
