export module grid;

import std;

template <typename TContainer>
concept grid_container_type =
   std::ranges::random_access_range<TContainer> &&
   requires(TContainer container)
   {
      typename TContainer::value_type;
      container.resize(1);
   };

export
template <typename T, grid_container_type TContainer = std::vector<std::optional<T>>>
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

   typename TContainer::value_type& at(std::size_t x, std::size_t y);

   const typename TContainer::value_type& at(std::size_t x, std::size_t y) const;

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

   TContainer cells_;
   std::size_t width_{0}, height_{0};
};

template <typename T, grid_container_type Container>
Grid<T, Container>::Grid(std::size_t width, std::size_t height):
   width_{width},
   height_{height}
{
   cells_.resize(width_ * height_);
}

template <typename T, grid_container_type Container>
void Grid<T, Container>::verifyCoordinate(std::size_t x, std::size_t y) const
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

template <typename T, grid_container_type Container>
const typename Container::value_type& Grid<T, Container>::at(std::size_t x, std::size_t y) const
{
   verifyCoordinate(x, y);
   return cells_[x + y * width_];
}

template <typename T, grid_container_type Container>
typename Container::value_type& Grid<T, Container>::at(std::size_t x, std::size_t y)
{
   return const_cast<typename Container::value_type&>(
      std::as_const(*this).at(x, y));
}
