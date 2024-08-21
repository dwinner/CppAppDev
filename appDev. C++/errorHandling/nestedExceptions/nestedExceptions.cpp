import std;

using namespace std;

class MyException : public exception
{
public:
   explicit MyException(string message) : message_{move(message)}
   {
   }

   const char* what() const noexcept override
   {
      return message_.c_str();
   }

private:
   string message_;
};


void DoSomething()
{
   try
   {
      throw runtime_error{"A runtime_error exception"};
   }
   catch (const runtime_error& /*e*/)
   {
      println("doSomething() caught a runtime_error");
      println("doSomething() throwing MyException");
      throw_with_nested(MyException{"MyException with nested runtime_error"});
   }
}

int main()
{
   try
   {
      DoSomething();
   }
   catch (const MyException& myEx)
   {
      println("main() caught MyException: {}", myEx.what());

      /*		const auto* nested{dynamic_cast<const nested_exception*>(&e)};
            if (nested) {
               try {
                  nested->rethrow_nested();
               } catch (const runtime_error& e) {
                  // Handle nested exception.
                  println("  Nested exception: {}", e.what());
               }
            }
      */
      try
      {
         rethrow_if_nested(myEx);
      }
      catch (const runtime_error& rtEx)
      {
         // Handle nested exception.
         println("  Nested exception: {}", rtEx.what());
      }
   }
}
