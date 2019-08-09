#include <memory>
#include <iostream>

using namespace std;

class Nothing
{
public:
	Nothing() { cout << "Nothing::Nothing()" << endl; }
	virtual ~Nothing() { cout << "Nothing::~Nothing()" << endl; }
};

void doubleDelete()
{
	Nothing* myNothing = new Nothing();
	shared_ptr<Nothing> smartPtr1(myNothing);
	shared_ptr<Nothing> smartPtr2(myNothing);
}

void noDoubleDelete()
{
	auto smartPtr1 = make_shared<Nothing>();
	shared_ptr<Nothing> smartPtr2(smartPtr1);
}

int main()
{
	//doubleDelete();  // BUG, might cause a crash!
	noDoubleDelete();

	return 0;
}
