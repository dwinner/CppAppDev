#pragma once

#include <cstddef>
#include <vector>

template <typename T>
class OneDGrid
{
public:
	explicit OneDGrid(size_t inSize = kDefaultSize);
	virtual ~OneDGrid();

	T& operator[](size_t x);
	const T& operator[](size_t x) const;

	void resize(size_t newSize);
	size_t getSize() const { return mElems.size(); }
	static const size_t kDefaultSize = 10;

private:
	std::vector<T> mElems;
};

template <typename T>
OneDGrid<T>::OneDGrid(size_t inSize)
{
	mElems.resize(inSize);
}

template <typename T>
OneDGrid<T>::~OneDGrid()
{
	// Nothing to do, the vector will clean up itself.
}

template <typename T>
void OneDGrid<T>::resize(size_t newSize)
{
	mElems.resize(newSize);
}

template <typename T>
T& OneDGrid<T>::operator[](size_t x)
{
	return mElems[x];
}

template <typename T>
const T& OneDGrid<T>::operator[](size_t x) const
{
	return mElems[x];
}

