#include "GameBoard.h"

// Microsoft Visual Studio requires you to omit the following two lines.
// However, some compilers require them.
//const size_t GameBoard::kDefaultWidth;
//const size_t GameBoard::kDefaultHeight;

GameBoard::GameBoard(size_t inWidth, size_t inHeight) :
mWidth(inWidth), mHeight(inHeight)
{
	mCells = new GamePiece*[mWidth];
	for (size_t i = 0; i < mWidth; i++) {
		mCells[i] = new GamePiece[mHeight];
	}
}

GameBoard::GameBoard(const GameBoard& src)
{
	copyFrom(src);
}

GameBoard::~GameBoard()
{
	// Free the old memory
	freeMemory();
}

void GameBoard::copyFrom(const GameBoard& src)
{
	mWidth = src.mWidth;
	mHeight = src.mHeight;
	mCells = new GamePiece*[mWidth];
	for (size_t i = 0; i < mWidth; i++) {
		mCells[i] = new GamePiece[mHeight];
	}
	for (size_t i = 0; i < mWidth; i++) {
		for (size_t j = 0; j < mHeight; j++) {
			mCells[i][j] = src.mCells[i][j];
		}
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

GameBoard& GameBoard::operator=(const GameBoard& rhs)
{
	// Check for self-assignment
	if (this == &rhs) {
		return *this;
	}
	// Free the old memory
	freeMemory();
	// Copy the new memory
	copyFrom(rhs);
	return *this;
}

void GameBoard::setPieceAt(size_t x, size_t y, const GamePiece& inElem)
{
	mCells[x][y] = inElem;
}

GamePiece& GameBoard::getPieceAt(size_t x, size_t y)
{
	return mCells[x][y];
}

const GamePiece& GameBoard::getPieceAt(size_t x, size_t y) const
{
	return mCells[x][y];
}
