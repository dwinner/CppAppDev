#include <functional>
#include <print>

using namespace std;

class BigData
{
};

class BigDataProcessor
{
public:
   explicit BigDataProcessor(unique_ptr<BigData> data) :
       data_{std::move(data)}
   {

   }

   void operator()() const
   {
      println("Processing BigData instance...");
   }

private:
   unique_ptr<BigData> data_;
};

int main()
{
   auto data{make_unique<BigData>()};
   const move_only_function<void() const> processor{BigDataProcessor{std::move(data)}};
   processor();
}
