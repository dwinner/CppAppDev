#include <iostream>
#include <print>
#include <vector>
#include <mdspan>

using namespace std;

template<typename T>
void print2Dmdspan(const T &mdSpan)
{
   for (size_t i{0}; i < mdSpan.extents().extent(0); ++i)
   {
      for (size_t j{0}; j < mdSpan.extents().extent(1); ++j)
      {
         print("{} ", mdSpan[i, j]);
      }

      println("");
   }
}

int main()
{
   vector vec{1, 2, 3, 4, 5, 6, 7, 8};

   {
      // View vec as a 2D array of 2 rows with 4 integers each,
      // using the default row-major layout policy.
      mdspan data2D{vec.data(), 2, 4};
      print2Dmdspan(data2D);
   }

   println("");

   {
      // View vec as a 2D array of 2 rows with 4 integers each,
      // using the column-major layout policy.
      mdspan<int, extents<int, 2, 4>, layout_left> data2D{vec.data()};
      print2Dmdspan(data2D);
   }

   println("");

   {
      // View vec as a 2D array of 2 rows with 4 integers each,
      // using the default row-major layout policy.
      mdspan<int, extents<int, 2, dynamic_extent>> data2D{vec.data(), 4};
      print2Dmdspan(data2D);
   }
}
