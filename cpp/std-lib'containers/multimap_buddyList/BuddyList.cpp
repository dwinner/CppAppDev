#include <ranges>
#include "BuddyList.hpp"

using namespace std;

void BuddyList::addBuddy(const string &name, const string &buddy)
{
   // Make sure this buddy isn't already there. We don't want
   // to insert an identical copy of the key/value pair.
   if (!isBuddy(name, buddy))
   {
      buddies_.insert({name, buddy}); // Using initializer_list
   }
}

void BuddyList::removeBuddy(const string &name, const string &buddy)
{
   // Obtain the beginning and end of the range of elements with
   // key 'name'. Use both lower_bound() and upper_bound() to demonstrate
   // their use. Otherwise, it's more efficient to call equal_range().
   auto begin{buddies_.lower_bound(name)};  // Start of the range
   auto end{buddies_.upper_bound(name)};    // End of the range

   // Iterate through the elements with key 'name' looking
   // for a value 'buddy'. If there are no elements with key 'name',
   // begin equals end, so the loop body doesn't execute.
   for (auto iter{begin}; iter != end; ++iter)
   {
      if (iter->second == buddy)
      {
         // We found a match! Remove it from the map.
         buddies_.erase(iter);
         break;
      }
   }
}

bool BuddyList::isBuddy(const string &name, const string &buddy) const
{
   // Obtain the beginning and end of the range of elements with
   // key 'name' using equal_range(), and structured bindings.
   auto [begin, end] {buddies_.equal_range(name)};

   // Iterate through the elements with key 'name' looking
   // for a value 'buddy'.
   for (auto iter{begin}; iter != end; ++iter)
   {
      if (iter->second == buddy)
      {
         // We found a match!
         return true;
      }
   }

   // No matches
   return false;
}

vector<string> BuddyList::getBuddies(const string &name) const
{
   /*
   // Obtain the beginning and end of the range of elements with
   // key 'name' using equal_range(), and structured bindings.
   auto [begin, end] { buddies_.equal_range(name)};

   // Create a vector with all names in the range (all buddies of name).
   vector<string> buddies;
   for (auto iter{ begin }; iter != end; ++iter) {
      buddies.push_back(iter->second);
   }

   return buddies;
   */

   // Or: using the range library.
   auto [begin, end] {buddies_.equal_range(name)};
   return ranges::subrange{begin, end} | views::values | ranges::to<vector>();
}
