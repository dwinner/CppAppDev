export module grid:pointers;

import :main;
import std;

export
template <typename U>
class Grid<U*>
{
public:
   explicit Grid(std::size_t width = defaultWidth, std::size_t height = defaultHeight);

   virtual ~Grid() = default;

   // Copy constructor and copy assignment operator.
   Grid(const Grid& src);

   Grid& operator=(const Grid& rhs);

   // Move constructor and move assignment operator.
   Grid(Grid&& src) noexcept;

   Grid& operator=(Grid&& rhs) noexcept;

   void swap(Grid& other) noexcept;

   std::unique_ptr<U>& at(std::size_t x, std::size_t y);

   const std::unique_ptr<U>& at(std::size_t x, std::size_t y) const;

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

   std::vector<std::unique_ptr<U>> cells_;
   std::size_t width_{0}, height_{0};
};

template <typename U>
Grid<U*>::Grid(std::size_t width, std::size_t height) :
   width_{width},
   height_{height}
{
   cells_.resize(width_ * height_);
}

template <typename U>
void Grid<U*>::swap(Grid& other) noexcept
{
   using std::swap;

   swap(width_, other.width_);
   swap(height_, other.height_);
   swap(cells_, other.cells_);
}

template <typename U>
Grid<U*>::Grid(const Grid& src)
   : Grid{src.width_, src.height_}
{
   // The ctor-initializer of this constructor delegates first to the
   // non-copy constructor to allocate the proper amount of memory.

   // The next step is to copy the data.
   for (std::size_t i{0}; i < cells_.size(); ++i)
   {
      // Make a deep copy of the element by using its copy constructor.
      if (src.cells_[i] != nullptr)
      {
         cells_[i] = std::make_unique<U>(*src.cells_[i]);
      }
   }
}

template <typename U>
Grid<U*>& Grid<U*>::operator=(const Grid& rhs)
{
   // Use copy-and-swap idiom.
   auto copy{rhs}; // Do all the work in a temporary instance
   swap(copy); // Commit the work with only non-throwing operations
   return *this;
}

template <typename U>
Grid<U*>::Grid(Grid&& src) noexcept
{
   swap(src);
}

template <typename U>
Grid<U*>& Grid<U*>::operator=(Grid&& rhs) noexcept
{
   auto moved{std::move(rhs)}; // Move rhs into moved (noexcept)
   swap(moved); // Commit the work with only non-throwing operations

   return *this;
}

template <typename U>
void Grid<U*>::verifyCoordinate(std::size_t x, std::size_t y) const
{
   if (x >= width_)
   {
      throw std::out_of_range{
         std::format("x ({}) must be less than width ({}).", x, width_)
      };
   }

   if (y >= height_)
   {
      throw std::out_of_range{
         std::format("y ({}) must be less than height ({}).", y, height_)
      };
   }
}

template <typename U>
const std::unique_ptr<U>& Grid<U*>::at(std::size_t x, std::size_t y) const
{
   verifyCoordinate(x, y);
   return cells_[x + y * width_];
}

template <typename U>
std::unique_ptr<U>& Grid<U*>::at(std::size_t x, std::size_t y)
{
   return const_cast<std::unique_ptr<U>&>(std::as_const(*this).at(x, y));
}
