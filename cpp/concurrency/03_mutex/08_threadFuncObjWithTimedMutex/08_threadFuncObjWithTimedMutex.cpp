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
         unique_lock lock{timedMutex_, 200ms};
         if (lock)
         {
            cout << format("Counter {} has value {}", id_, i) << endl;
         }
         else
         {
            // Lock not acquired in 200ms, skip output.
         }
      }
   }

private:
   int id_{0};
   int numIterations_{0};
   inline static timed_mutex timedMutex_;
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
