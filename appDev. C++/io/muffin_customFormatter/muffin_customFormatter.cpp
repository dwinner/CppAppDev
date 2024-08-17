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

private:
   string description_;
   int size_{0};
   bool hasChocolateChips_{false};
};

template <>
class std::formatter<Muffin>
{
public:
   constexpr auto parse(auto& context)
   {
      return begin(context);
   }

   auto format(const Muffin& muffin, auto& ctx) const
   {
      ctx.advance_to(format_to(
         ctx.out(),
         "{}, size is {}, {}",
         muffin.getDescription(),
         muffin.getSize(),
         (muffin.hasChocolateChips() ? "has chips" : "no chips")));
      return ctx.out();
   }
};


int main()
{
   println("Let's create a muffin in code and print it.");

   Muffin myMuffin;
   myMuffin.setDescription("Giant Blueberry Muffin");
   myMuffin.setSize(42);
   myMuffin.setHasChocolateChips(false);

   println("The muffin is a {} -- yummy!", myMuffin);
}
