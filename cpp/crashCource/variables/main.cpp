#include <iostream>
#include <format>

void varSample();

void types();

void numericLimits();

void castingSample();

int main()
{
   varSample();
   types();
   numericLimits();
   castingSample();

   return 0;
}

void varSample()
{
   int uninitializedInt;
   int initializedInt{7};

   using namespace std;
   cout << format("{} is a random value", uninitializedInt) << endl;
   cout << format("{} was assigned as an initial value", initializedInt) << endl;
}

void types()
{
   int i1{-7};
   signed int i2{-6};
   signed i3{-5};

   short s1{13};
   short int s2{14};
   signed short s3{15};
   signed short int s4{16};

   long l{-7L};

   long long ll{14LL};

   unsigned int ui{2U};
   unsigned uj{5U};
   unsigned short us{23U};
   unsigned long ul{5400UL};
   unsigned long long ull{140ULL};

   float f{7.2f};

   double d{7.2};

   long double ld{16.98L};

   char ch{'m'};

   char8_t c8{u8'm'};
   char16_t c16{u'm'};
   char32_t c32{U'm'};

   wchar_t w{L'm'};

   bool b1{true};

   std::byte b2{42};
}

void numericLimits()
{
   using namespace std;

   cout << "int:" << endl;
   cout << format("Max int value: {}", numeric_limits<int>::max()) << endl;
   cout << format("Min int value: {}", numeric_limits<int>::min()) << endl;
   cout << format("Lowest int value: {}", numeric_limits<int>::lowest()) << endl;

   cout << "\ndouble:" << endl;
   cout << format("Max double value: {}", numeric_limits<double>::max()) << endl;
   cout << format("Min double value: {}", numeric_limits<double>::min()) << endl;
   cout << format("Lowest double value: {}", numeric_limits<double>::lowest()) << endl;
}

void castingSample()
{
   float myFloat{3.14f};
   int i1{(int) myFloat};                // method 1
   int i2{int(myFloat)};                // method 2
   int i3{static_cast<int>(myFloat)};   // method 3

   short someShort{16};
   long someLong{someShort};          // no explicit cast needed
}