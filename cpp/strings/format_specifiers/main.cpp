//import std;

using namespace std;

int main()
{
   {
      // width
      int i{42};
      println("|{:5}|", i);       // |   42|
      println("|{:{}}|", i, 7);   // |     42|
      println("|{1:{0}}|", 7, i); // |     42|
   }

   println("");

   {
      // [fill]align
      int i{42};
      println("|{:7}|", i);     // |     42|
      println("|{:<7}|", i);    // |42     |
      println("|{:_>7}|", i);   // |_____42|
      println("|{:_^7}|", i);   // |__42___|

      println("|{:=>16}|", "");  // |================|
   }

   println("");

   {
      // sign
      int i{42};
      println("|{:<5}|", i);   // |42   |
      println("|{:<+5}|", i);  // |+42  |
      println("|{:< 5}|", i);  // | 42  |
      println("|{:< 5}|", -i); // |-42  |
   }

   println("");

   {
      // Integral types
      int i{42};
      println("|{:10d}|", i);   // |        42|
      println("|{:10b}|", i);   // |    101010|
      println("|{:#10b}|", i);  // |  0b101010|
      println("|{:10X}|", i);   // |        2A|
      println("|{:#10X}|", i);  // |      0X2A|
   }

   println("");

   {
      // String types
      string s{"ProCpp"};
      println("|{:_^10}|", s); // |__ProCpp__|
   }

   println("");

   {
      // Floating-point types
      double d{3.1415 / 2.3};
      println("|{:12g}|", d);                         // |     1.36587|
      println("|{:12.2}|", d);                        // |         1.4|
      println("|{:12e}|", d);                         // |1.365870e+00|

      int width{12};
      int precision{3};
      println("|{2:{0}.{1}f}|", width, precision, d); // |       1.366|
      println("|{2:{0}.{1}}|", width, precision, d);  // |        1.37|
   }

   println("");

   {
      // 0
      int i{42};
      println("|{:06d}|", i);   // |000042|
      println("|{:+06d}|", i);  // |+00042|
      println("|{:06X}|", i);   // |00002A|
      println("|{:#06X}|", i);  // |0X002A|
   }

   println("");

   {
      float f{1.2f};
      cout << format(std::locale{"nl"}, "|{:Lg}|\n", f);  // |1,2|
   }

   println("");

   // Escaped output
   println("|{:?}|", "Hello\tWorld!\n");  // |Hello\tWorld!\n|
   println("|{:?}|", "\"");               // |"\""|
   println("|{:?}|", '\'');               // |'\''|
   println("|{:?}|", '"');                // |'"'|

   // ranges
   vector values{ 11, 22, 33 };
   println("{}", values);         // [11, 22, 33]
   println("{:n}", values);       // 11, 22, 33

   println("{{{:n}}}", values);   // {11, 22, 33}

   println("{:*^16}", values);    // **[11, 22, 33]**
   println("{:*^16n}", values);   // ***11, 22, 33***

   println("{::*^6}", values);    // [**11**, **22**, **33**]

   println("{:n:*^6}", values);   // **11**, **22**, **33**

   vector strings{ "Hello"s, "World!\t2023"s };
   println("{}", strings);        // ["Hello", "World!\t2023"]
   println("{:}", strings);       // ["Hello", "World!\t2023"]
   println("{::}", strings);      // [Hello, World!    2023]
   println("{:n:}", strings);     // Hello, World!    2023

   vector chars{ 'W', 'o', 'r', 'l', 'd', '\t', '!' };
   println("{}", chars);          // ['W', 'o', 'r', 'l', 'd', '\t', '!']
   println("{::#x}", chars);      // [0x57, 0x6f, 0x72, 0x6c, 0x64, 0x9, 0x21]
   println("{:s}", chars);        // World    !
   println("{:?s}", chars);       // "World\t!"

   pair p{ 11, 22 };
   println("{}", p);              // (11, 22)
   println("{:n}", p);            // 11, 22
   println("{:m}", p);            // 11: 22

   vector<vector<int>> vv{ {11, 22}, {33, 44, 55} };
   println("{}", vv);             // [[11, 22], [33, 44, 55]]
   println("{:n}", vv);           // [11, 22], [33, 44, 55]
   println("{:n:n}", vv);         // 11, 22, 33, 44, 55
   println("{:n:n:*^4}", vv);     // *11*, *22*, *33*, *44*, *55*
}
