#include <print>
#include <string>

using namespace std;

class IParagraph
{
public:
   virtual ~IParagraph() = default;  // Always a virtual destructor!
   virtual std::string getHTML() const = 0;
};

class Paragraph : public IParagraph
{
public:
   explicit Paragraph(std::string text) : text_{std::move(text)}
   {}

   std::string getHTML() const override
   {
      return format("<p>{}</p>", text_);
   }

private:
   std::string text_;
};

class BoldParagraph : public IParagraph
{
public:
   explicit BoldParagraph(const IParagraph &paragraph) : wrapped_{paragraph}
   {}

   std::string getHTML() const override
   {
      return format("<b>{}</b>", wrapped_.getHTML());
   }

private:
   const IParagraph &wrapped_;
};

class ItalicParagraph : public IParagraph
{
public:
   explicit ItalicParagraph(const IParagraph &paragraph) : wrapped_{paragraph}
   {}

   std::string getHTML() const override
   {
      return format("<i>{}</i>", wrapped_.getHTML());
   }

private:
   const IParagraph &wrapped_;
};


int main()
{
   Paragraph text{"A party? For me? Thanks!"};

   // Bold
   println("{}", BoldParagraph{text}.getHTML());

   // Bold and Italic
   println("{}", ItalicParagraph{BoldParagraph{text}}.getHTML());
}
