module game_board;

import std;

using namespace std;

GameBoard::GameBoard(size_t width, size_t height) :
   width_{width},
   height_{height}
{
   cells_.resize(width_ * height_);
}

GameBoard::GameBoard(const GameBoard& src)
   : GameBoard{src.width_, src.height_}
{
   // The ctor-initializer of this constructor delegates first to the
   // non-copy constructor to allocate the proper amount of memory.
   // The next step is to copy the data.
   for (size_t i{0}; i < cells_.size(); ++i)
   {
      if (src.cells_[i])
      {
         cells_[i] = src.cells_[i]->clone();
      }
   }
}

void GameBoard::verifyCoordinate(size_t x, size_t y) const
{
   if (x >= width_)
   {
      throw out_of_range{format("x ({}) must be less than width ({}).", x, width_)};
   }

   if (y >= height_)
   {
      throw out_of_range{format("y ({}) must be less than height ({}).", y, height_)};
   }
}

void GameBoard::swap(GameBoard& other) noexcept
{
   std::swap(width_, other.width_);
   std::swap(height_, other.height_);
   std::swap(cells_, other.cells_);
}

void Swap(GameBoard& first, GameBoard& second) noexcept
{
   first.swap(second);
}

GameBoard& GameBoard::operator=(const GameBoard& rhs)
{
   // Copy-and-swap idiom
   GameBoard temp{rhs}; // Do all the work in a temporary instance
   swap(temp); // Commit the work with only non-throwing operations
   return *this;
}

const unique_ptr<GamePiece>& GameBoard::at(size_t x, size_t y) const
{
   verifyCoordinate(x, y);
   return cells_[x + y * width_];
}

unique_ptr<GamePiece>& GameBoard::at(size_t x, size_t y)
{
   return const_cast<unique_ptr<GamePiece>&>(as_const(*this).at(x, y));
}
