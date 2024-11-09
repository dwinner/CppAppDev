import std;

using namespace std;

once_flag OnceFlag;

void initializeSharedResources()
{
   // ... Initialize shared resources to be used by multiple threads.
   println("Shared resources initialized.");
}

void processingFunction()
{
   // Make sure the shared resources are initialized.
   call_once(OnceFlag, initializeSharedResources);

   // ... Do some work, including using the shared resources
   println("Processing");
}

int main()
{
   // Launch 3 threads.
   for (vector<jthread> threads{3}; auto& jThr : threads)
   {
      jThr = jthread{processingFunction};
   }

   // No need to manually call join(), as we are using jthread.
}
