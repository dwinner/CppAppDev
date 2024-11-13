export module simple_wrapper;

import std;

export template <typename T> requires (std::floating_point<T> || std::integral<T>)
class SimpleWrapper
{
public:
   explicit SimpleWrapper(T& object) : obj_{object}
   {
   }

   T& get() const
   {
      return obj_;
   }

private:
   T& obj_;
};
