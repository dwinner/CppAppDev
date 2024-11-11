import std;

using namespace std;

template <typename TupleType, int N = tuple_size_v<TupleType>>
void tuplePrint(const TupleType& tupleType)
{
   if constexpr (N > 1)
   {
      tuplePrint<TupleType, N - 1>(tupleType);
   }

   println("{}", get<N - 1>(tupleType));
}

int main()
{
   tuple t1{16, "Test"s, true};
   tuplePrint(t1);
}
