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
         println("Counter {} has value {}", id_, i);
      }
   }

private:
   int id_{0};
   int numIterations_{0};
};

int main()
{
   // Using uniform initialization syntax.
   thread t1{Counter{1, 20}};

   // Using named variable.
   Counter c{2, 12};
   thread t2{c};

   // Wait for threads to finish.
   t1.join();
   t2.join();
}
