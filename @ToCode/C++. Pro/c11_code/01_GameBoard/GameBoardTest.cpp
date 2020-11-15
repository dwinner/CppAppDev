#include "GameBoard.h"

class ChessPiece : public GamePiece
{
public:
	virtual std::unique_ptr<GamePiece> clone() const override;
};

std::unique_ptr<GamePiece> ChessPiece::clone() const
{
	// Call the copy constructor to copy this instance
	return std::make_unique<ChessPiece>(*this);
}

void processGameBoard(const GameBoard& board)
{
	const std::unique_ptr<GamePiece>& pawn = board.getPieceAt(0, 0);

	// Doesn't compile
	//board.setPieceAt(1, 2, make_unique<ChessPiece>());
}

int main()
{
	GameBoard chessBoard(8, 8);
	auto pawn = std::make_unique<ChessPiece>();
	chessBoard.setPieceAt(0, 0, std::move(pawn));
	chessBoard.setPieceAt(0, 1, std::make_unique<ChessPiece>());
	chessBoard.setPieceAt(0, 1, nullptr);

	GameBoard board2;
	board2 = chessBoard;

	processGameBoard(board2);

	return 0;
}
