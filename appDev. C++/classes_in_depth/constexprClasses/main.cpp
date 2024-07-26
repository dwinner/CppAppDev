#include <iostream>

using namespace std;

class Matrix
{
public:
   Matrix() = default; // Implicitly constexpr

   constexpr explicit Matrix(unsigned rows, unsigned columns)
       : _rows{rows},
         _columns{columns}
   {
   }

   [[nodiscard]] constexpr unsigned getSize() const
   {
      return _rows * _columns;
   }

private:
   unsigned _rows{0}, _columns{0};
};

int main()
{
   constexpr Matrix matrix{8, 2};
   int linearizedMatrix[matrix.getSize()];
   cout << format("Size of linearizedMatrix = {}", size(linearizedMatrix)) << endl;

   constexpr Matrix matrixDefault;

   return 0;
}
