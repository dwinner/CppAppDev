export module logger;

import std;

export class Logger
{
public:
   // Starts a background thread writing log entries to a file.
   Logger();

   // Gracefully shut down background thread.
   virtual ~Logger();

   // Prevent copy construction and assignment.
   Logger(const Logger&) = delete;

   Logger& operator=(const Logger&) = delete;

   // Add log entry to the queue.
   void log(std::string entry);

private:
   // The function running in the background thread.
   void processEntries();

   // Helper member function to process a queue of entries.
   void processEntriesHelper(std::queue<std::string>& queue, std::ofstream& ofs) const;

   // Boolean telling the background thread to terminate.
   bool exit_{false};

   // Mutex and condition variable to protect access to the queue.
   std::mutex mutex_;
   std::condition_variable condVar_;
   std::queue<std::string> queue_;

   // The background thread.
   std::thread thread_;
};
