import std;

using namespace std;

class Muffin final
{
public:
   const string& getDescription() const
   {
      return description_;
   }

   void setDescription(string description)
   {
      description_ = std::move(description);
   }

   int getSize() const
   {
      return size_;
   }

   void setSize(int size)
   {
      size_ = size;
   }

   bool hasChocolateChips() const
   {
      return hasChocolateChips_;
   }

   void setHasChocolateChips(bool hasChips)
   {
      hasChocolateChips_ = hasChips;
   }

   void output() const
   {
      printf("%s, size is %d, %s",
             getDescription().c_str(),
             getSize(),
             (hasChocolateChips() ? "has chips" : "no chips"));
   }

private:
   string description_;
   int size_{0};
   bool hasChocolateChips_{false};
};

int main()
{
   println("Let's create a muffin in code and print it.");

   Muffin myMuffin;
   myMuffin.setDescription("Giant Blueberry Muffin");
   myMuffin.setSize(42);
   myMuffin.setHasChocolateChips(false);

   printf("The muffin is a ");
   myMuffin.output();
   printf(" -- yummy!\n");
}
