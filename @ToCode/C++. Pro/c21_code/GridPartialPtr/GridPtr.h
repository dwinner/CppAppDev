#pragma once

#include "Grid.h"
#include <cstddef>
#include <memory>

template <typename T>
class Grid<T*>
{
public:
	explicit Grid(size_t inWidth = kDefaultWidth, size_t inHeight = kDefaultHeight);
	Grid(const Grid<T*>& src);
	virtual ~Grid();
	Grid<T*>& operator=(const Grid<T*>& rhs);

	// The Grid becomes the owner of the element!
	void setElementAt(size_t x, size_t y, std::unique_ptr<T> inElem);
	T* getElementAt(size_t x, size_t y);
	const T* getElementAt(size_t x, size_t y) const;

	size_t getHeight() const { return mHeight; }
	size_t getWidth() const { return mWidth; }
	static const size_t kDefaultWidth = 10;
	static const size_t kDefaultHeight = 10;

private:
	void initializeCellsContainer();
	void copyFrom(const Grid<T*>& src);
	std::vector<std::vector<std::unique_ptr<T>>> mCells;
	size_t mWidth, mHeight;
}; 

template <typename T>
Grid<T*>::Grid(size_t inWidth, size_t inHeight)
: mWidth(inWidth)
, mHeight(inHeight)
{
	initializeCellsContainer();
}

template <typename T>
Grid<T*>::Grid(const Grid<T*>& src)
{
	copyFrom(src);
}

template <typename T>
Grid<T*>::~Grid()
{
	// Nothing to do, the vector and the smart pointers will clean up themselves.
}

template <typename T>
void Grid<T*>::initializeCellsContainer()
{
	// clear() will clean up all vectors and smart pointers.
	mCells.clear();

	mCells.resize(mWidth);
	for (auto& column : mCells) {
		column.resize(mHeight);
	}
}

template <typename T>
void Grid<T*>::copyFrom(const Grid<T*>& src)
{
	mWidth = src.mWidth;
	mHeight = src.mHeight;

	initializeCellsContainer();

	for (size_t i = 0; i < mWidth; i++) {
		for (size_t j = 0; j < mHeight; j++) {
			// Make a deep copy of the element by using its copy constructor.
			if (src.mCells[i][j]) {
				mCells[i][j].reset(new T(*(src.mCells[i][j])));
			}
		}
	}
}

template <typename T>
Grid<T*>& Grid<T*>::operator=(const Grid<T*>& rhs)
{
	// Check for self-assignment.
	if (this == &rhs) {
		return *this;
	}

	// Perform the copy.
	copyFrom(rhs);

	return *this;
}

template <typename T>
void Grid<T*>::setElementAt(size_t x, size_t y, std::unique_ptr<T> inElem)
{
	mCells[x][y] = std::move(inElem);
}

template <typename T>
T* Grid<T*>::getElementAt(size_t x, size_t y)
{
	return mCells[x][y].get();
}

template <typename T>
const T* Grid<T*>::getElementAt(size_t x, size_t y) const
{
	return mCells[x][y].get();
}
