export module article_citations;

import std;

export class ArticleCitations
{
public:
   explicit ArticleCitations(const std::string& filename);

   virtual ~ArticleCitations();

   ArticleCitations(const ArticleCitations& src);

   ArticleCitations& operator=(const ArticleCitations& rhs);

   const std::string& getArticle() const;

   int getNumCitations() const;

   const std::string& getCitation(int i) const;

private:
   void readFile(const std::string& filename);

   void copy(const ArticleCitations& src);

   std::string article_;
   std::string* citations_{nullptr};
   int numCitations_{0};
};
