import std;

using namespace std;

static constexpr unsigned number_of_threads{50};
static constexpr unsigned loops_per_thread{100};

void Dowork(const unsigned threadNumber, vector<unsigned>& data, atomic_flag& spinlock)
{
   for (unsigned i{0}; i < loops_per_thread; ++i)
   {
      while (spinlock.test_and_set())
      {
      }

      // Spins until lock is acquired.
      // Safe to handle shared data...
      data.push_back(threadNumber);
      spinlock.clear(); // Releases the acquired lock.
   }
}

int main()
{
   vector<unsigned> data;
   atomic_flag dataSpinlock;
   vector<jthread> threads;
   for (unsigned i{0}; i < number_of_threads; ++i)
   {
      threads.emplace_back(Dowork, i, ref(data), ref(dataSpinlock));
   }

   for (auto& jThr : threads)
   {
      jThr.join();
   }

   println("data contains {} elements, expected {}.",
           data.size(),
           number_of_threads * loops_per_thread);
}
