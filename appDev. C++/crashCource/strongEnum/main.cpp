#include <iostream>
#include <utility>

using namespace std;

enum class PieceType
{
   King = 1,
   Queen,
   Rook = 10,
   Pawn
};

int main()
{
   {
      PieceType piece{PieceType::King};
      auto underlyingValue{to_underlying(piece)};
      cout << underlyingValue << endl;
   }

   {
      using enum PieceType;
      PieceType piece{King};
      cout << to_underlying(piece) << endl;
   }

   {
      using PieceType::King;
      PieceType piece{King};
      piece = PieceType::Queen;
   }

   return 0;
}
