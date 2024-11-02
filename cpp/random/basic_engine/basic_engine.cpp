import std;

using namespace std;

int main()
{
   random_device seeder;
   mt19937 engine{seeder()};

   constexpr int low{1};
   constexpr int high{99};
   uniform_int_distribution<int> distribution{low, high};

   for (int i{low}; i < high; ++i)
   {
      println("{}", distribution(engine));
   }
}
