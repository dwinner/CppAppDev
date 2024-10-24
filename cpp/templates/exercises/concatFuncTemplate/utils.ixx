export module utils;

import std;

using namespace std;

export template <typename T>
concept supports_to_string = requires(const T& t) { to_string(t); };

export auto Concat(const supports_to_string auto& t1, const supports_to_string auto& t2)
{
   return to_string(t1) + to_string(t2);
}

export auto Concat(string_view t1, string_view t2)
{
   return string{t1} + string{t2};
}

export auto Concat(string_view t1, const supports_to_string auto& t2)
{
   return string{t1} + to_string(t2);
}

export auto Concat(const supports_to_string auto& t1, string_view t2)
{
   return to_string(t1) + string{t2};
}
