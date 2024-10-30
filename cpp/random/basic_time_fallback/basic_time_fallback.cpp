import std;

using namespace std;

int main()
{
   random_device seeder;
   const auto seed{seeder.entropy() ? seeder() : time(nullptr)};
   mt19937 engine{static_cast<mt19937::result_type>(seed)};

   constexpr int low{1};
   constexpr int high{99};
   uniform_int_distribution<int> distribution{low, high};
   for (int i{low}; i < high; ++i)
   {
      println("{}", distribution(engine));
   }
}
