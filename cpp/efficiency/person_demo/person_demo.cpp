import std;

using namespace std;

class Person
{
public:
   Person();

   explicit Person(string firstName, string lastName, int age);

   Person(const Person& rhs);

   virtual ~Person();

   const string& getFirstName() const
   {
      return firstName_;
   }

   const string& getLastName() const
   {
      return lastName_;
   }

   int getAge() const
   {
      return age_;
   }

private:
   string firstName_;
   string lastName_;
   int age_{0};
};

Person::Person()
{
   println("Default Ctor");
}

Person::Person(string firstName, string lastName, int age)
   : firstName_{move(firstName)}, lastName_{move(lastName)}, age_{age}
{
   println("Ctor");
}

Person::~Person()
{
   println("Dtor");
}

Person::Person(const Person& rhs)
   : firstName_{rhs.firstName_}, lastName_{rhs.lastName_}, age_{rhs.age_}
{
   println("Copy ctor");
}

ostream& operator<<(ostream& ostr, const Person& p)
{
   ostr << p.getFirstName() << " " << p.getLastName() <<
      " " << p.getAge() << endl;

   return ostr;
}


/*
void processPerson(Person p)
{
// process the person
}
*/


void processPerson(const Person& /*p*/)
{
   // process the person
}

int main()
{
   Person me{"Marc", "Gregoire", 42};
   processPerson(me);
}
