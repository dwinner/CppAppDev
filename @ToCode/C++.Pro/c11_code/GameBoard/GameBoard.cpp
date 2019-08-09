#include "GameBoard.h"

using namespace std;

GameBoard::GameBoard(size_t inWidth, size_t inHeight)
: mWidth(inWidth)
, mHeight(inHeight)
{
	initializeCellsContainer();
}

GameBoard::GameBoard(const GameBoard& src)
{
	copyFrom(src);
}

GameBoard::~GameBoard()
{
	// Nothing to do, the vector will clean up itself.
}

void GameBoard::initializeCellsContainer()
{
	mCells.resize(mWidth);
	for (auto& column : mCells) {
		column.resize(mHeight);
	}
}

void GameBoard::copyFrom(const GameBoard& src)
{
	mWidth = src.mWidth;
	mHeight = src.mHeight;

	initializeCellsContainer();

	for (size_t i = 0; i < mWidth; i++) {
		for (size_t j = 0; j < mHeight; j++) {
			if (src.mCells[i][j])
				mCells[i][j] = src.mCells[i][j]->clone();
			else
				mCells[i][j].reset();
		}
	}
}

GameBoard& GameBoard::operator=(const GameBoard& rhs)
{
	// check for self-assignment
	if (this == &rhs) {
		return *this;
	}

	// copy the source GameBoard
	copyFrom(rhs);

	return *this;
}

void GameBoard::setPieceAt(size_t x, size_t y, unique_ptr<GamePiece> inPiece)
{
	mCells[x][y] = move(inPiece);
}

unique_ptr<GamePiece>& GameBoard::getPieceAt(size_t x, size_t y)
{
	return mCells[x][y];
}

const unique_ptr<GamePiece>& GameBoard::getPieceAt(size_t x, size_t y) const
{
	return mCells[x][y];
}
