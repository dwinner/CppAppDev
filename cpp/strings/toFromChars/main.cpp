#include <iostream>
#include <format>

using namespace std;

int main()
{
   const size_t BufferSize{50};

   {
      // to_chars() without structured binding.
      string out(BufferSize, ' '); // A string of BufferSize space characters.
      auto result{to_chars(out.data(), out.data() + out.size(), 12345)};
      if (result.ec == errc{})
      {
         cout << std::format("{}", out) << endl; /* Conversion successful. */
      }
   }

   {
      // to_chars() with structured binding.
      string out(BufferSize, ' '); // A string of BufferSize space characters.
      auto [ptr, error] {to_chars(out.data(), out.data() + out.size(), 12345)};
      if (error == errc{})
      {
         cout << std::format("{}", out) << endl; /* Conversion successful. */
      }
   }

   {
      // Demonstrating perfect round-tripping.
      double value1{0.314};
      string out(BufferSize, ' '); // A string of BufferSize space characters.
      auto [ptr1, error1] {to_chars(out.data(), out.data() + out.size(), value1)};
      if (error1 == errc{})
      {
         cout << std::format("{}", out) << endl; /* Conversion successful. */
      }

      double value2;
      auto [ptr2, error2] {from_chars(out.data(), out.data() + out.size(), value2)};
      if (error2 == errc{})
      {
         if (value1 == value2)
         {
            cout << std::format("Perfect roundtrip") << endl;
         }
         else
         {
            cout << std::format("No perfect roundtrip?!?") << endl;
         }
      }
   }

   return 0;
}
