#pragma once

#include "Grid.h"
#include <cstddef>
#include <string>

template <size_t WIDTH, size_t HEIGHT>
class Grid<const char*, WIDTH, HEIGHT>
{
public:
	Grid();
	virtual ~Grid();

	void setElementAt(size_t x, size_t y, const char* inElem);
	const char* getElementAt(size_t x, size_t y) const;

	size_t getHeight() const { return HEIGHT; }
	size_t getWidth() const { return WIDTH; }

private:
	std::string mCells[WIDTH][HEIGHT];
};

template <size_t WIDTH, size_t HEIGHT>
Grid<const char*, WIDTH, HEIGHT>::Grid() : mCells()		// Zero-initialize mCells
{
}

template <size_t WIDTH, size_t HEIGHT>
Grid<const char*, WIDTH, HEIGHT>::~Grid()
{
	// Nothing to do.
}

template <size_t WIDTH, size_t HEIGHT>
void Grid<const char*, WIDTH, HEIGHT>::setElementAt(size_t x, size_t y, const char* inElem)
{
	// Convert the given const char* string into an std::string
	if (inElem)
		mCells[x][y] = inElem;
	else
		mCells[x][y] = "";
}

template <size_t WIDTH, size_t HEIGHT>
const char* Grid<const char*, WIDTH, HEIGHT>::getElementAt(size_t x, size_t y) const
{
	return mCells[x][y].c_str();
}
