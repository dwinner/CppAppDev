#pragma once

#include <cstddef>
#include "Grid.h"

template <typename T>
class GameBoard : public Grid<T>
{
public:
	explicit GameBoard(size_t inWidth = Grid<T>::kDefaultWidth,
		size_t inHeight = Grid<T>::kDefaultHeight);
	void move(size_t xSrc, size_t ySrc, size_t xDest, size_t yDest);
};

template <typename T>
GameBoard<T>::GameBoard(size_t inWidth, size_t inHeight)
: Grid<T>(inWidth, inHeight)
{
}

template <typename T>
void GameBoard<T>::move(size_t xSrc, size_t ySrc, size_t xDest, size_t yDest)
{
	this->setElementAt(xDest, yDest, this->getElementAt(xSrc, ySrc));
	this->setElementAt(xSrc, ySrc, T()); // default construct the src cell
}
