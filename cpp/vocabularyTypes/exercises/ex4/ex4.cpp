import std;

using namespace std;
using Parameter = pair<string, variant<bool, int, string>>;

Parameter ParseParameter(const char* parameter)
{
   const regex nameValRegEx{"(.*)=(.*)"};
   if (cmatch matchResults;
      regex_match(parameter, matchResults, nameValRegEx))
   {
      const auto& name{matchResults[1].str()};
      const auto& value{matchResults[2].str()};

      // Try to parse as Boolean.
      if (value == "true")
      {
         return {name, true};
      }

      if (value == "false")
      {
         return {name, false};
      }

      // Try to parse as integer.
      try
      {
         int parsedInteger{stoi(value)};
         return {name, parsedInteger};
      }
      catch (const exception&)
      {
         // Could not parse as integer, just interpret as string.
         return {name, value};
      }
   }

   throw invalid_argument{"Cannot parse parameter."};
}

class CommandLineParameterVisitor
{
public:
   explicit CommandLineParameterVisitor(string parameterName)
      : parameterName_{move(parameterName)}
   {
   }

   void operator()(bool value)
   {
      println("Boolean: {} -> {}", parameterName_, value);
   }

   void operator()(int value)
   {
      println("Integer: {} -> {}", parameterName_, value);
   }

   void operator()(string value)
   {
      println("String: {} -> {}", parameterName_, value);
   }

private:
   string parameterName_;
};

int main(int argc, char** argv)
{
   for (int i{0}; i < argc; ++i)
   {
      try
      {
         auto parameter{ParseParameter(argv[i])};
         CommandLineParameterVisitor visitor{parameter.first};
         visit(visitor, parameter.second);
      }
      catch (const invalid_argument&)
      {
         // Could not parse parameter, ignore it.
      }
   }
}
