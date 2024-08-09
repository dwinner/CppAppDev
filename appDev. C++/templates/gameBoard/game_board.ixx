export module game_board;

import std;

export class GamePiece
{
public:
   virtual ~GamePiece() = default;

   virtual std::unique_ptr<GamePiece> clone() const = 0;
};

export class GameBoard
{
public:
   explicit GameBoard(
      std::size_t width = defaultWidth,
      std::size_t height = defaultHeight);

   GameBoard(const GameBoard& src); // copy constructor

   virtual ~GameBoard() = default; // virtual defaulted destructor

   GameBoard& operator=(const GameBoard& rhs); // assignment operator

   // Explicitly default a move constructor and move assignment operator.
   GameBoard(GameBoard&& src) = default;

   GameBoard& operator=(GameBoard&& src) = default;

   std::unique_ptr<GamePiece>& at(std::size_t x, std::size_t y);

   const std::unique_ptr<GamePiece>& at(std::size_t x, std::size_t y) const;

   std::size_t getHeight() const
   {
      return height_;
   }

   std::size_t getWidth() const
   {
      return width_;
   }

   static constexpr std::size_t defaultWidth{10};

   static constexpr std::size_t defaultHeight{10};

   void swap(GameBoard& other) noexcept;

private:
   void verifyCoordinate(std::size_t x, std::size_t y) const;

   std::vector<std::unique_ptr<GamePiece>> cells_;
   std::size_t width_{0}, height_{0};
};

export void Swap(GameBoard& first, GameBoard& second) noexcept;
