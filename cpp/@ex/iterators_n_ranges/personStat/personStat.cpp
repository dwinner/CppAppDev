import std;
import person;

using namespace std;
using EmpPair = pair<Person, int>;

template <input_iterator InputIter,output_iterator<iter_reference_t<InputIter>> OutputIter>
void Copy(InputIter begin, InputIter end, OutputIter target)
{
   for (auto iter{begin}; iter != end; ++iter, ++target)
   {
      *target = *iter;
   }
}

vector<EmpPair> NewEmpDb()
{
   vector<EmpPair> empDb;
   empDb.push_back(make_pair(Person{"Joe", "Doe"}, 56));
   empDb.push_back(make_pair(Person{"Den", "Win"}, 34));
   empDb.push_back(make_pair(Person{"Alex", "Vole"}, 78));
   empDb.push_back(make_pair(Person{"Bruce", "Ekkel"}, 67));
   empDb.push_back(make_pair(Person{"Billy", "The Kid"}, 11));
   empDb.push_back(make_pair(Person{"Marine", "Sazone"}, 8));
   empDb.push_back(make_pair(Person{"Alen", "Delone"}, 88));

   return empDb;
}

void FilterLegal(const vector<pair<Person, int>>& empDb)
{
   const auto legalAges{
      empDb
      | views::filter([](const auto& val)
      {
         return val.second >= 12 && val.second <= 65;
      })
      | views::transform([](const auto& empPair)
      {
         return empPair.second;
      })
      | ranges::to<vector<int>>()
   };

   if (!legalAges.empty())
   {
      int sum = 0;
      for (const int age : legalAges)
      {
         sum += age;
      }

      int avgAge = sum / legalAges.size();
      println("The average age is {}", avgAge);
   }
}

int main()
{
   vector<EmpPair> empDb = NewEmpDb();
   unordered_set<string> outEmps;

   auto first4Emps{
      views::take(4)
      | views::transform([](const auto& val)
      {
         return val.getFirstName();
      })
      | ranges::to<vector<string>>()
   };

   for (const auto& item : first4Emps)
   {
      println("{}", item);
   }

   return 0;
}
