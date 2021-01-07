/**
 * Using STL functions
 */

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>

struct Review
{
   std::string title;
   int rating;
};

bool operator<(const Review &firstReview, const Review &secondReview);

bool worseThan(const Review &firstReview, const Review &secondReview);

bool fillReview(Review &aReview);

void showReview(const Review &aReview);

int main()
{
   using namespace std;

   vector<Review> books;
   Review temp;
   while (fillReview(temp))
   {
      books.push_back(temp);
   }

   if (!books.empty())
   {
      cout << "Thank you. You entered the following "
           << books.size() << " ratings:\n"
           << "Rating\tBook\n";
      for_each(books.begin(), books.end(), showReview);

      sort(books.begin(), books.end());
      cout << "Sorted by title:\nRating\tBook\n";
      for_each(books.begin(), books.end(), showReview);

      sort(books.begin(), books.end(), worseThan);
      cout << "Sorted by rating:\nRating\tBook\n";
      for_each(books.begin(), books.end(), showReview);

      shuffle(books.begin(), books.end(), std::mt19937(std::random_device()()));
      cout << "After shuffling:\nRating\tBook\n";
      for_each(books.begin(), books.end(), showReview);
   }
   else
   {
      cout << "No entries. ";
   }
   cout << "Bye.\n";

   return 0;
}

bool operator<(const Review &firstReview, const Review &secondReview)
{
   return firstReview.title < secondReview.title
          ? true
          : firstReview.title == secondReview.title && firstReview.rating < secondReview.rating;
}

bool worseThan(const Review &firstReview, const Review &secondReview)
{
   return firstReview.rating < secondReview.rating;
}

bool fillReview(Review &aReview)
{
   std::cout << "Enter book title (quit to quit): ";
   std::getline(std::cin, aReview.title);
   if (aReview.title == "quit")
   {
      return false;
   }

   std::cout << "Enter book rating: ";
   std::cin >> aReview.rating;
   if (!std::cin)
   {
      return false;
   }

   // get rid of rest of input line
   while (std::cin.get() != '\n')
   {
      continue;
   }

   return true;
}

void showReview(const Review &aReview)
{
   std::cout << aReview.rating << "\t" << aReview.title << std::endl;
}
