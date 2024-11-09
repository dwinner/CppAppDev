import std;

using namespace std;

void initializeSharedResources()
{
   // ... Initialize shared resources to be used by multiple threads.
   println("Shared resources initialized.");
}

atomic<bool> Initialized{false};
mutex Mutex;

void processingFunction()
{
   if (!Initialized)
   {
      unique_lock lock{Mutex};
      if (!Initialized)
      {
         initializeSharedResources();
         Initialized = true;
      }
   }

   print("1");
}

int main()
{
   vector<jthread> threads;
   for (int i{0}; i < 5; ++i)
   {
      threads.emplace_back(processingFunction);
   }

   // No need to manually call join(), as we are using jthread.
}
