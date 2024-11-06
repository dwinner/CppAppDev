import std;

using namespace std;

template <typename Tuple, size_t... Indices>
void tuplePrintHelper(const Tuple& tuple, index_sequence<Indices...>)
{
   (println("{}", get<Indices>(tuple)), ...);
}

template <typename... Args>
void tuplePrint(const tuple<Args...>& tuple)
{
   tuplePrintHelper(tuple, make_index_sequence<sizeof...(Args)>{});
}

int main()
{
   tuple t1{16, "Test"s, true};
   tuplePrint(t1);
}
