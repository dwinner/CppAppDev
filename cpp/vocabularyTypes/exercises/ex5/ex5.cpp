import std;

using namespace std;
using Parameter = tuple<string, variant<bool, int, string>>;

Parameter parseParameter(const char* parameter)
{
   regex nameValRegEx{"(.*)=(.*)"};
   if (cmatch subMatches;
      regex_match(parameter, subMatches, nameValRegEx))
   {
      const auto& name{subMatches[1].str()};
      const auto& value{subMatches[2].str()};

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
         auto parameter{parseParameter(argv[i])};
         CommandLineParameterVisitor visitor{get<string>(parameter)};
         visit(visitor, get<1>(parameter));
      }
      catch (const invalid_argument&)
      {
         // Could not parse parameter, ignore it.
      }
   }
}
