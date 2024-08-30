export module grid:definition;

import std;

export
template <typename T>
class Grid
{
public:
   explicit Grid(std::size_t width = defaultWidth, std::size_t height = defaultHeight);

   virtual ~Grid() = default;

   // Explicitly default a copy constructor and copy assignment operator.
   Grid(const Grid& src) = default;

   Grid& operator=(const Grid& rhs) = default;

   // Explicitly default a move constructor and move assignment operator.
   Grid(Grid&& src) = default;

   Grid& operator=(Grid&& rhs) = default;

   std::optional<T>& at(std::size_t x, std::size_t y);

   const std::optional<T>& at(std::size_t x, std::size_t y) const;

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

private:
   void verifyCoordinate(std::size_t x, std::size_t y) const;

   std::vector<std::optional<T>> cells_;
   std::size_t width_{0}, height_{0};
};
