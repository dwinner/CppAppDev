#pragma once

#include <cstddef>
#include <string>

// When the template specialization is used, the original template must be
// visible too. Including it here ensures that it will always be visible
// when this specialization is visible.
#include "Grid.h"

template <>
class Grid<const char*>
{
public:
	explicit Grid(size_t inWidth = kDefaultWidth, size_t inHeight = kDefaultHeight);
	virtual ~Grid();

	void setElementAt(size_t x, size_t y, const char* inElem);
	const char* getElementAt(size_t x, size_t y) const;

	size_t getHeight() const { return mHeight; }
	size_t getWidth() const { return mWidth; }
	static const size_t kDefaultWidth = 10;
	static const size_t kDefaultHeight = 10;

private:
	void initializeCellsContainer();
	std::vector<std::vector<std::string>> mCells;
	size_t mWidth, mHeight;
};

Grid<const char*>::Grid(size_t inWidth, size_t inHeight)
: mWidth(inWidth)
, mHeight(inHeight)
{
	initializeCellsContainer();
}

Grid<const char*>::~Grid()
{
	// Nothing to do, the vector will clean up itself.
}

void Grid<const char*>::initializeCellsContainer()
{
	mCells.resize(mWidth);
	for (auto& column : mCells) {
		column.resize(mHeight);
	}
}

void Grid<const char*>::setElementAt(size_t x, size_t y, const char* inElem)
{
	// Convert the given char* string into an std::string
	if (inElem)
		mCells[x][y] = inElem;
	else
		mCells[x][y] = "";
}

const char* Grid<const char*>::getElementAt(size_t x, size_t y) const
{
	return mCells[x][y].c_str();
}
