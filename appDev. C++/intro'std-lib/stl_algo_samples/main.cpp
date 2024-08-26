/**
 * Using several STL elements
 */

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>
#include <cctype>

using namespace std;

char toLower(char ch)
{
   return tolower(ch);
}

string &ToLower(string &st);

void display(const string &s);

int main()
{
   vector<string> words;
   cout << "Enter words (enter quit to quit):\n";
   string input;
   while (cin >> input && input != "quit")
   {
      words.push_back(input);
   }

   cout << "You entered the following words:\n";
   for_each(words.begin(), words.end(), display);
   cout << endl;

   // place words in set, converting to lowercase
   set<string> wordSet;
   transform(words.begin(), words.end(),
             insert_iterator<set<string>>(wordSet, wordSet.begin()),
             ToLower);
   cout << "\nAlphabetic list of words:\n";
   for_each(wordSet.begin(), wordSet.end(), display);
   cout << endl;

   // place word and frequency in map
   map<string, int> wordMap;
   set<string>::iterator si;
   for (si = wordSet.begin(); si != wordSet.end(); si++)
   {
      wordMap[*si] = count(words.begin(), words.end(), *si);
   }

   // display map contents
   cout << "\nWord frequency:\n";
   for (si = wordSet.begin(); si != wordSet.end(); si++)
   {
      cout << *si << ": " << wordMap[*si] << endl;
   }

   return 0;
}

string &ToLower(string &st)
{
   transform(st.begin(), st.end(), st.begin(), toLower);
   return st;
}

void display(const string &s)
{
   cout << s << " ";
}
