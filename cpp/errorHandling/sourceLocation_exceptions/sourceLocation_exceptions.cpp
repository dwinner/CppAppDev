import std;

using namespace std;

class MyException : public exception
{
public:
   explicit MyException(string message,
                        source_location location = source_location::current())
      : message_{move(message)},
        location_{move(location)}
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

private:
   string message_;
   source_location location_;
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
      const auto& location{e.where()};
      println(cerr, "Caught: '{}' at line {} in {}.",
              e.what(),
              location.line(),
              location.function_name());
   }
}
