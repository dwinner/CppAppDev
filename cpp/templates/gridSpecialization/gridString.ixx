export module grid:string;

import std;

// When the template specialization is used, the original template must be
// visible too.
import :main;

export
template <>
class Grid<const char*>
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

   std::optional<std::string>& at(std::size_t x, std::size_t y);

   const std::optional<std::string>& at(std::size_t x, std::size_t y) const;

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

   std::vector<std::optional<std::string>> cells_;
   std::size_t width_{0};
   std::size_t height_{0};
};

Grid<const char*>::Grid(std::size_t width, std::size_t height)
   : width_{width},
     height_{height}
{
   cells_.resize(width_ * height_);
}

void Grid<const char*>::verifyCoordinate(std::size_t x, std::size_t y) const
{
   if (x >= width_)
   {
      throw std::out_of_range{std::format("x ({}) must be less than width ({}).", x, width_)};
   }

   if (y >= height_)
   {
      throw std::out_of_range{std::format("y ({}) must be less than height ({}).", y, height_)};
   }
}

const std::optional<std::string>& Grid<const char*>::at(std::size_t x, std::size_t y) const
{
   verifyCoordinate(x, y);
   return cells_[x + y * width_];
}

std::optional<std::string>& Grid<const char*>::at(std::size_t x, std::size_t y)
{
   return const_cast<std::optional<std::string>&>(std::as_const(*this).at(x, y));
}
