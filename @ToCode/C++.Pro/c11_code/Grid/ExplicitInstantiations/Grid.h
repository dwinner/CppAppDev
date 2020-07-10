#pragma once

#include <cstddef>
#include <vector>

template <typename T>
class Grid
{
public:
	explicit Grid(size_t inWidth = kDefaultWidth, size_t inHeight = kDefaultHeight);
	virtual ~Grid();

	// Sets an element at a given location. The element is copied.
	void setElementAt(size_t x, size_t y, const T& inElem);
	T& getElementAt(size_t x, size_t y);
	const T& getElementAt(size_t x, size_t y) const;

	size_t getHeight() const { return mHeight; }
	size_t getWidth() const { return mWidth; }
	static const size_t kDefaultWidth = 10;
	static const size_t kDefaultHeight = 10;

private:
	void initializeCellsContainer();
	std::vector<std::vector<T>> mCells;
	size_t mWidth, mHeight;
};
