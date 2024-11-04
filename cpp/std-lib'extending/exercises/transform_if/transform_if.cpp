import std;

using namespace std;

template <forward_iterator ForwardIterator,
   output_iterator<iter_reference_t<ForwardIterator>> OutputIterator,
   indirect_unary_predicate<ForwardIterator> Predicate,
   invocable<iter_reference_t<ForwardIterator>> UnaryOperation>
OutputIterator TransformIf(
   ForwardIterator first, ForwardIterator last, OutputIterator output, Predicate pred, UnaryOperation op)
{
   auto iter{first};
   while (iter != last)
   {
      if (invoke(pred, *iter))
      {
         *output = op(*iter);
      }
      else
      {
         *output = *iter;
      }

      ++output;
      ++iter;
   }

   return output;
}

int main()
{
   array values{1, 2, 3, 4, 5, 6, 7, 8, 9};
   for (const auto& item : values)
   {
      print("{} ", item);
   }

   println("");

   vector<int> result;
   TransformIf(begin(values), end(values), back_insert_iterator{result},
               [](const auto& value)
               {
                  return value % 2 != 0;
               },
               [](const auto& value)
               {
                  return value * 2;
               });

   for (const auto& item : result)
   {
      print("{} ", item);
   }
}
