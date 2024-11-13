module article_citations;

import std;

using namespace std;

ArticleCitations::ArticleCitations(const string& filename)
{
   // All we have to do is read the file.
   readFile(filename);
}

ArticleCitations::ArticleCitations(const ArticleCitations& src)
{
   copy(src);
}

ArticleCitations& ArticleCitations::operator=(const ArticleCitations& rhs)
{
   // Check for self-assignment.
   if (this == &rhs)
   {
      return *this;
   }

   // Free the old memory.
   delete[] citations_;

   // Copy the data.
   copy(rhs);

   return *this;
}

void ArticleCitations::copy(const ArticleCitations& src)
{
   // Copy the article name, author, etc.
   article_ = src.article_;

   // Copy the number of citations.
   numCitations_ = src.numCitations_;

   // Allocate an array of the correct size.
   citations_ = new string[numCitations_];

   // Copy each element of the array.
   for (int i{0}; i < numCitations_; ++i)
   {
      citations_[i] = src.citations_[i];
   }
}

ArticleCitations::~ArticleCitations()
{
   delete [] citations_;
}

void ArticleCitations::readFile(const string& filename)
{
   // Open the file and check for failure.
   ifstream inputFile{filename};
   if (inputFile.fail())
   {
      throw invalid_argument{"Unable to open file"};
   }

   // Read the article author, title, etc. line.
   getline(inputFile, article_);

   // Skip the whitespace before the citations start.
   inputFile >> ws;

   int count{0};

   // Save the current position, so we can return to it.
   const streampos citationsStart{inputFile.tellg()};

   // First count the number of citations.
   println("readFile(): counting number of citations");
   while (!inputFile.eof())
   {
      // Skip whitespace before the next entry.
      inputFile >> ws;
      string temp;
      getline(inputFile, temp);
      if (!temp.empty())
      {
         println("Citation {}: {}", count, temp);
         ++count;
      }
   }

   println("Found {} citations", count);
   println("readFile(): reading citations");
   if (count != 0)
   {
      // Allocate an array of strings to store the citations.
      citations_ = new string[count];
      numCitations_ = count;

      // Seek back to the start of the citations.
      inputFile.seekg(citationsStart);

      // Read each citation and store it in the new array.
      for (count = 0; count < numCitations_; ++count)
      {
         string temp;
         getline(inputFile, temp);
         if (!temp.empty())
         {
            println("{}", temp);
            citations_[count] = temp;
         }
      }
   }
   else
   {
      numCitations_ = -1;
   }

   println("readFile(): finished");
}

const string& ArticleCitations::getArticle() const
{
   return article_;
}

int ArticleCitations::getNumCitations() const
{
   return numCitations_;
}

const string& ArticleCitations::getCitation(const int i) const
{
   return citations_[i];
}
