
class MyClass
{
public:
   explicit MyClass(int)
   {}

   explicit MyClass(int, int)
   {}
};


void process(const MyClass &c)
{}

int main()
{
   process(MyClass{1});
   process(MyClass{1, 2});

   return 0;
}
