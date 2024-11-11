import std;

using namespace std;

class Calculator
{
public:
   explicit Calculator(int a, int b) : a_{a}, b_{b}
   {
   }

   void operator()()
   {
      result_ = a_ * b_;
   }

   int getResult() const
   {
      return result_;
   }

private:
   int a_{0};
   int b_{0};
   int result_{0};
};

int main()
{
   Calculator calculator{21, 2};
   jthread job{ref(calculator)};
   job.join();
   println("21*2 = {}", calculator.getResult());
}
