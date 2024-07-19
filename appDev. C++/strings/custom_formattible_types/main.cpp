#include <iostream>
#include <format>
#include "KeyValue.h"

using namespace std;

int main()
{
   const size_t len{34}; // Label field length
   KeyValue kv{"Key 1", 255};

   println("{:>{}} {}", "Default:", len, kv);
   println("{:>{}} {:k}", "Key only:", len, kv);
   println("{:>{}} {:v}", "Value only:", len, kv);
   println("{:>{}} {:b}", "Key and value with default format:", len, kv);

   println("{:>{}} {:k:*^11}", "Key only with special format:", len, kv);
   println("{:>{}} {:v::#06X}", "Value only with special format:", len, kv);
   println("{:>{}} {::*^11:#06X}", "Key and value with special format:", len, kv);

   try
   {
      auto formatted{vformat("{:cd}", make_format_args(kv))};
      println("{}", formatted);
   }
   catch (const format_error &caught_exception)
   {
      println("{}", caught_exception.what());
   }

   return 0;
}
