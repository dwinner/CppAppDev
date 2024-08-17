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
      ctx.advance_to(format_to(ctx.out(), "{}, size is {}, {}",
                               muffin.getDescription(),
                               muffin.getSize(),
                               (muffin.hasChocolateChips() ? "has chips" : "no chips"))
      );
      return ctx.out();
   }
};

Muffin CreateMuffin(istringstream& stream);

int main()
{
   println("First, let's create a muffin in code and output it.");

   Muffin myMuffin;
   myMuffin.setDescription("Giant Blueberry Muffin");
   myMuffin.setSize(42);
   myMuffin.setHasChocolateChips(false);

   println("The muffin is a {} -- yummy!", myMuffin);
   println("Now we'll create a muffin from a string stream.");

   istringstream instream{"\"Raspberry Muffin\" 12 true"};
   Muffin muffin2{CreateMuffin(instream)};
   println("The parsed muffin is a {}.", muffin2);
}

Muffin CreateMuffin(istringstream& stream)
{
   Muffin muffin;
   // Assume data is properly formatted:
   // "Description" size chips

   string description;
   int size;
   bool hasChips;

   // Read all three values. Note that chips is represented
   // by the strings "true" and "false".
   stream >> quoted(description) >> size >> boolalpha >> hasChips;
   if (stream)
   {
      // Reading was successful.
      muffin.setSize(size);
      muffin.setDescription(description);
      muffin.setHasChocolateChips(hasChips);
   }

   return muffin;
}
