#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
	Person();
	Person(const string& inFirstName, const string& inLastName, int inAge);
	virtual ~Person();
	Person(const Person& rhs);
	const string& getFirstName() const { return mFirstName; }
	const string& getLastName() const { return mLastName; }
	int getAge() const { return mAge; }

	friend ostream& operator<<(ostream& ostr, const Person& p);

private:
	string mFirstName, mLastName;
	int mAge;
};

Person::Person() : mAge(0)
{
	cout << "Default Ctor" << endl;
}

Person::Person(const string& inFirstName, const string& inLastName, int inAge)
	: mFirstName(inFirstName), mLastName(inLastName), mAge(inAge)
{
	cout << "Ctor" << endl;
}

Person::~Person()
{
	cout << "dtor" << endl;
}

Person::Person(const Person& rhs)
	: mFirstName(rhs.mFirstName), mLastName(rhs.mLastName), mAge(rhs.mAge)
{
	cout << "Copy ctor" << endl;
}

ostream& operator<<(ostream& ostr, const Person& p)
{
	ostr << p.mFirstName << " " << p.mLastName <<
		" " << p.mAge << endl;

	return ostr;
}


/*
void processPerson(Person p)
{
// process the person
}
*/

void processPerson(const Person& p)
{
	// process the person
}

Person createPerson()
{
	Person newP;
	return newP;
}

int main()
{
	Person me("Marc", "Gregoire", 35);
	processPerson(me);
	
	cout << "-----" << endl;

	cout << createPerson();
	createPerson();

	return 0;
}
