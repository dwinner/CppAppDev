#include "GameBoard.h"
#include <stdexcept>
#include <new>

using namespace std;

// Microsoft Visual Studio requires you to omit the following two lines.
// However, some compilers require them.
//const size_t GameBoard::kDefaultWidth;
//const size_t GameBoard::kDefaultHeight;

GameBoard::GameBoard(size_t inWidth, size_t inHeight) :
mWidth(inWidth), mHeight(inHeight)
{
	allocateMemory();
}

void GameBoard::allocateMemory()
{
	size_t i = 0;
	mCells = new GamePiece*[mWidth];

	try {
		for (i = 0; i < mWidth; i++) {
			mCells[i] = new GamePiece[mHeight];
		}
	} catch (...) {
		// allocateMemory() is called from the constructor and from the
		// copy constructor, so we need to clean up any memory we already
		// allocated, because the destructor will never get called.
		// The upper bound of the for loop is the index of the last
		// element in the mCells array that we tried to allocate 
		// (the one that failed). All indices before that one store
		// pointers to allocated memory that must be freed.
		for (size_t j = 0; j < i; j++) {
			delete[] mCells[j];
		}
		// allocateMemory() is called from the constructor, from the
		// copy constructor, and indirectly called from operator=. In the
		// latter case the object was already constructed, so the
		// destructor will be called at some point.
		// So, set mCells, mWidth, and mHeight to values that will allow
		// the destructor to run without harming anything.
		delete[] mCells;
		mCells = nullptr;
		mWidth = 0;
		mHeight = 0;

		// translate any exception to bad_alloc
		throw bad_alloc();
	}
}

void GameBoard::freeMemory()
{
	for (size_t i = 0; i < mWidth; i++) {
		delete[] mCells[i];
	}
	delete[] mCells;
	mCells = nullptr;
	mWidth = 0;
	mHeight = 0;
}

GameBoard::GameBoard(const GameBoard& src)
{
	copyFrom(src);
}

GameBoard::~GameBoard() noexcept
{
	// free the old memory
	freeMemory();
}

GameBoard& GameBoard::operator=(const GameBoard& rhs)
{
	// check for self-assignment
	if (this == &rhs) {
		return *this;
	}

	// free the old memory
	freeMemory();

	// copy the new memory
	copyFrom(rhs);

	return *this;
}

void GameBoard::copyFrom(const GameBoard& src)
{
	mWidth = src.mWidth;
	mHeight = src.mHeight;

	allocateMemory();

	// Copy data.
	for (size_t i = 0; i < mWidth; i++) {
		for (size_t j = 0; j < mHeight; j++) {
			mCells[i][j] = src.mCells[i][j];
		}
	}
}

void GameBoard::setPieceAt(size_t x, size_t y, const GamePiece& inElem)
{
	// Check for out of range arguments
	if (x < 0)
		throw out_of_range("GameBoard::setPieceAt: x-coordinate negative");
	if (x >= mWidth)
		throw out_of_range("GameBoard::setPieceAt: x-coordinate beyond width");
	if (y < 0)
		throw out_of_range("GameBoard::setPieceAt: y-coordinate negative");
	if (y >= mHeight)
		throw out_of_range("GameBoard::setPieceAt: y-coordinate beyond height");

	mCells[x][y] = inElem;
}

GamePiece& GameBoard::getPieceAt(size_t x, size_t y)
{
	// Check for out of range arguments
	if (x < 0)
		throw out_of_range("GameBoard::getPieceAt: x-coordinate negative");
	if (x >= mWidth)
		throw out_of_range("GameBoard::getPieceAt: x-coordinate beyond width");
	if (y < 0)
		throw out_of_range("GameBoard::getPieceAt: y-coordinate negative");
	if (y >= mHeight)
		throw out_of_range("GameBoard::getPieceAt: y-coordinate beyond height");

	return mCells[x][y];
}

const GamePiece& GameBoard::getPieceAt(size_t x, size_t y) const
{
	// Check for out of range arguments
	if (x < 0)
		throw out_of_range("GameBoard::getPieceAt const: x-coordinate negative");
	if (x >= mWidth)
		throw out_of_range("GameBoard::getPieceAt const: x-coordinate beyond width");
	if (y < 0)
		throw out_of_range("GameBoard::getPieceAt const: y-coordinate negative");
	if (y >= mHeight)
		throw out_of_range("GameBoard::getPieceAt const: y-coordinate beyond height");

	return mCells[x][y];
}
