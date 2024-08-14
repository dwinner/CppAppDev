import std;

const std::string message{"Test"};

const std::string& GetString()
{
   return message;
}

int main()
{
   auto s1{GetString()};
   const auto& s2{GetString()};
   decltype(GetString()) s3{GetString()};
   decltype(auto) s4{GetString()};
}
