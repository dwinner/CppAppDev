import std;

using namespace std;

class Request
{
public:
   explicit Request(int id) : id_{id}
   {
   }

   void process()
   {
      println("Processing request {}", id_);
   }

private:
   int id_{0};
};

int main()
{
   Request req{100};
   thread t{&Request::process, &req};

   t.join();
}
