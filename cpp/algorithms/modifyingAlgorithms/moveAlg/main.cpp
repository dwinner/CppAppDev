#include <algorithm>
#include <print>
#include <string>
#include <vector>

using namespace std;

class MyClass
{
public:
   MyClass() = default;

   MyClass(const MyClass &src) = default;

   explicit MyClass(string str) : str_{std::move(str)}
   {}

   virtual ~MyClass() = default;

   // Move assignment operator
   MyClass &operator=(MyClass &&rhs) noexcept
   {
      if (this == &rhs)
      {
         return *this;
      }

      str_ = std::move(rhs.str_);
      println("Move operator= (str_={})", str_);

      return *this;
   }

   void setString(string str)
   {
      str_ = std::move(str);
   }

   const string &getString() const
   {
      return str_;
   }

private:
   string str_;
};

int main()
{
   vector<MyClass> vecSrc{MyClass{"a"}, MyClass{"b"}, MyClass{"c"}};
   vector<MyClass> vecDst(vecSrc.size());
   move(begin(vecSrc), end(vecSrc), begin(vecDst));
   for (const auto &item: vecDst)
   {
      print("{} ", item.getString());
   }
}
