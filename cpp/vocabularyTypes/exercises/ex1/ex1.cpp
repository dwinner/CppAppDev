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

variant<vector<int>, Error> getData(bool fail)
{
   if (fail)
   {
      return Error{"An error occurred."};
   }

   return vector{11, 22, 33};
}

void handleResult(const variant<vector<int>, Error>& result)
{
   if (holds_alternative<Error>(result))
   {
      println("Error: {}", get<Error>(result).getMessage());
   }
   else
   {
      for (auto& data{get<vector<int>>(result)}; const auto& vecItem : data)
      {
         print("{} ", vecItem);
      }
   }
}

int main()
{
   handleResult(getData(false));
   handleResult(getData(true));
}
