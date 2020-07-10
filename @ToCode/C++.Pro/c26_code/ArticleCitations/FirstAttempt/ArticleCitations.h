#pragma once

#include <string>

class ArticleCitations
{
public:
	ArticleCitations(const std::string& fileName);
	virtual ~ArticleCitations();
	ArticleCitations(const ArticleCitations& src);
	ArticleCitations& operator=(const ArticleCitations& rhs);

	const std::string& getArticle() const { return mArticle; }
	int getNumCitations() const { return mNumCitations; }
	const std::string& getCitation(int i) const { return mCitations[i]; }

private:
	void readFile(const std::string& fileName);
	void copy(const ArticleCitations& src);

	std::string mArticle;
	std::string* mCitations;
	int mNumCitations;
};
