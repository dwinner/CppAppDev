import grid;
import std;

using namespace std;

template <typename T>
void FillGrid(Grid<T>& grid)
{
   T index{0};
   for (size_t y{0}; y < grid.getHeight(); ++y)
   {
      for (size_t x{0}; x < grid.getWidth(); ++x)
      {
         grid.at(x, y) = ++index;
      }
   }
}

template <typename T>
void PrintGrid(const Grid<T>& grid)
{
   for (size_t y{0}; y < grid.getHeight(); ++y)
   {
      for (size_t x{0}; x < grid.getWidth(); ++x)
      {
         const auto& element{grid.at(x, y)};
         if (element.has_value())
         {
            print("{}\t", element.value());
         }
         else
         {
            print("n/a\t");
         }
      }

      println("");
   }
}

int main()
{
   Grid<int> grid1{2, 2};
   Grid<int> grid2{3, 3};

   FillGrid(grid1);
   println("grid1:");
   PrintGrid(grid1);

   FillGrid(grid2);
   println("\ngrid2:");
   PrintGrid(grid2);

   auto result{grid1 + grid2};

   println("\ngrid1 + grid2:");
   PrintGrid(result);
}
