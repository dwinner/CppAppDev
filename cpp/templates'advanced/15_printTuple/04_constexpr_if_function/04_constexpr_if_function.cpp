import std;

using namespace std;

template <typename TupleType, int N>
void TuplePrintHelper(const TupleType& tupleType)
{
   if constexpr (N > 1)
   {
      TuplePrintHelper<TupleType, N - 1>(tupleType);
   }

   println("{}", get<N - 1>(tupleType));
}

template <typename T>
void TuplePrint(const T& tuple)
{
   TuplePrintHelper<T, tuple_size_v<T>>(tuple);
}

int main()
{
   const tuple t1{16, "Test"s, true};
   TuplePrint(t1);
}
