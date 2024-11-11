import std;

using namespace std;

class Counter
{
public:
   explicit Counter(int id, int numIterations):
      id_{id},
      numIterations_{numIterations}
   {
   }

   void operator()() const
   {
      for (int i{0}; i < numIterations_; ++i)
      {
         osyncstream syncedCout{cout};
         syncedCout << format("Counter {} has value {}", id_, i);
         syncedCout << endl;
         // Upon destruction, syncedCout atomically flushes
         // its contents into cout.
      }
   }

private:
   int id_{0};
   int numIterations_{0};
};

int main()
{
   // Using uniform initialization syntax
   jthread t1{Counter{1, 20}};

   // Using named variable
   Counter c{2, 12};
   jthread t2{c};

   // No need to manually call join(), as we are using jthread.
}
