import std;

using namespace std;

int main()
{
   constexpr unsigned int start{1};
   constexpr unsigned int end{20};
   constexpr unsigned int iterations{1'000'000};

   random_device seeder;
   mt19937 engine{seeder()};
   exponential_distribution<double> distribution{0.5};
   auto generator{bind(distribution, engine)};
   map<int, int> histogram;
   for (unsigned int i{0}; i < iterations; ++i)
   {
      int randomNumber{static_cast<int>(generator())};
      // Search map for a key=randomNumber. If found, add 1 to the value associated
      // with that key. If not found, add the key to the map with value 1.
      ++(histogram[randomNumber]);
   }

   // Write to a CSV file.
   ofstream of{"res.csv"};
   for (unsigned int i{start}; i <= end; ++i)
   {
      of << i << ";" << histogram[i] << endl;
   }

   // Draw histogram to the standard output console.
   for (unsigned int i{start}; i <= end; ++i)
   {
      println("{:2} {}", i, string(histogram[i] / 3000, '*'));
   }
}