#include <iostream>
#include <format>

using namespace std;

void helper(string &&message)
{
}

// lvalue reference parameter
void handleMessage(string &message)
{
   cout << format("handleMessage with lvalue reference: {}", message) << endl;
}

// rvalue reference parameter
void handleMessage(string &&message)
{
   cout << format("handleMessage with rvalue reference: {}", message) << endl;
   helper(std::move(message));
}

int main()
{
   string value{"Hello "};

   // wrap lvalue to rvalue
   handleMessage(auto{value});

   // std behavior
   handleMessage(value);

   string a{"Hello "};
   string b{"World"};

   // Handle a named variable
   handleMessage(a);             // Calls handleMessage(string& value)

   // Handle an expression
   handleMessage(a + b);         // Calls handleMessage(string&& value)

   // Handle a literal
   handleMessage("Hello World"); // Calls handleMessage(string&& value)

   // Handle a named variable and force to use rvalue reference function
   handleMessage(std::move(b));  // Calls handleMessage(string&& value)

   return 0;
}
