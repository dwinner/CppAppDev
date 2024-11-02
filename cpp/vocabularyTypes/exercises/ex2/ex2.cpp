import std;

using namespace std;

class Error
{
public:
   explicit Error(string message) : message_{move(message)}
   {
   }

   const string& getMessage() const
   {
      return message_;
   }

private:
   string message_;
};

expected<vector<int>, Error> getData(bool fail)
{
   if (fail)
   {
      return unexpected{Error{"An error occurred."}};
   }

   return vector{11, 22, 33};
}

void handleResult(const expected<vector<int>, Error>& result)
{
   if (!result.has_value())
   {
      println("Error: {}", result.error().getMessage());
   }
   else
   {
      for (const auto& item : result.value())
      {
         print("{} ", item);
      }

      println("");
   }
}

int main()
{
   handleResult(getData(false));
   handleResult(getData(true));
}
