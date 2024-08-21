import std;

using namespace std;

class MyException : public exception
{
public:
   explicit MyException(string message,
                        source_location location = source_location::current())
      : message_{move(message)}
        , location_{move(location)}
        , stackTrace_{stacktrace::current(1)} // 1 means skip top frame.
   {
   }

   const char* what() const noexcept override
   {
      return message_.c_str();
   }

   virtual const source_location& where() const noexcept
   {
      return location_;
   }

   virtual const stacktrace& how() const noexcept
   {
      return stackTrace_;
   }

private:
   string message_;
   source_location location_;
   stacktrace stackTrace_;
};

void DoSomething()
{
   throw MyException{"Throwing MyException."};
}

int main()
{
   try
   {
      DoSomething();
   }
   catch (const MyException& e)
   {
      // Print exception description + location where exception was raised.
      const auto& location{e.where()};
      println(cerr, "Caught: '{}' at line {} in {}.",
              e.what(),
              location.line(),
              location.function_name());

      // Print the stack trace at the point where the exception was raised.
      println(cerr, "  Stack trace:");
      for (unsigned index{0}; auto&& frame : e.how())
      {
         const string& fileName{frame.source_file()};
         println(cerr, "    {}> {}, {}({})",
                 index++,
                 frame.description(),
                 (fileName.empty() ? "n/a" : fileName),
                 frame.source_line());
      }
   }
}
