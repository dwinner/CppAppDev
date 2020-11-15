#pragma once

#include <cstddef>
#include <vector>

template <typename T, size_t N>
class NDGrid
{
public:
	explicit NDGrid(size_t inSize = kDefaultSize);
	virtual ~NDGrid();

	NDGrid<T, N-1>& operator[](size_t x);
	const NDGrid<T, N-1>& operator[](size_t x) const;

	void resize(size_t newSize);
	size_t getSize() const { return mElems.size(); }
	static const size_t kDefaultSize = 10;

private:
	std::vector<NDGrid<T, N-1>> mElems;
};

template <typename T>
class NDGrid<T, 1>
{
public:
	explicit NDGrid(size_t inSize = kDefaultSize);
	virtual ~NDGrid();

	T& operator[](size_t x);
	const T& operator[](size_t x) const;

	void resize(size_t newSize);
	size_t getSize() const { return mElems.size(); }
	static const size_t kDefaultSize = 10;

private:
	std::vector<T> mElems;
};

template <typename T, size_t N>
NDGrid<T, N>::NDGrid(size_t inSize)
{
	resize(inSize);
}

template <typename T, size_t N>
NDGrid<T, N>::~NDGrid()
{
	// Nothing to do, the vector will clean up itself.
}

template <typename T, size_t N>
void NDGrid<T, N>::resize(size_t newSize)
{
	mElems.resize(newSize);

	// Resizing the vector calls the 0-argument constructor for
	// the NDGrid<T, N-1> elements, which constructs
	// it with the default size. Thus, we must explicitly call
	// resize() on each of the elements to recursively resize all
	// nested Grid elements.
	for (auto& element : mElems) {
		element.resize(newSize);
	}
}

template <typename T, size_t N>
NDGrid<T, N-1>& NDGrid<T, N>::operator[](size_t x)
{
	return mElems[x];
}

template <typename T, size_t N>
const NDGrid<T, N-1>& NDGrid<T, N>::operator[](size_t x) const
{
	return mElems[x];
}

////////////////////////


template <typename T>
NDGrid<T, 1>::NDGrid(size_t inSize)
{
	resize(inSize);
}

template <typename T>
NDGrid<T, 1>::~NDGrid()
{
	// Nothing to do, the vector will clean up itself.
}

template <typename T>
void NDGrid<T, 1>::resize(size_t newSize)
{
	mElems.resize(newSize);
}

template <typename T>
T& NDGrid<T, 1>::operator[](size_t x)
{
	return mElems[x];
}

template <typename T>
const T& NDGrid<T, 1>::operator[](size_t x) const
{
	return mElems[x];
}
