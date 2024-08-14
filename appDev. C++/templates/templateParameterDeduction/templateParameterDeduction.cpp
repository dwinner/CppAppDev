template <typename RetType, typename T1, typename T2>
RetType AddA(const T1& t1, const T2& t2)
{
   return t1 + t2;
}

template <typename RetType = long long, typename T1, typename T2>
RetType AddB(const T1& t1, const T2& t2)
{
   return t1 + t2;
}

int main()
{
   auto result1{AddA<long long, int, int>(1, 2)};
   auto result2{AddA<long long>(1, 2)};

   auto result{AddB(1, 2)};
}
