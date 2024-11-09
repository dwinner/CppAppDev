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
         lock_guard lock{mutex_};
         cout << format("Counter {} has value {}", id_, i) << endl;
      }
   }

private:
   int id_{0};
   int numIterations_{0};
   inline static mutex mutex_;
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
