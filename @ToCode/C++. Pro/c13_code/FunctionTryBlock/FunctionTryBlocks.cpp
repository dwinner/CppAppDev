#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

class SubObject
{
	public:
		SubObject(int i);
};

SubObject::SubObject(int /*i*/)
{
	throw runtime_error("Exception by SubObject ctor");
}

class MyClass
{
	public:
		MyClass();
	private:
		SubObject mSubObject;
};

MyClass::MyClass()
try
	: mSubObject(42)
{
	/* ... constructor body ... */
}
catch (const exception& e)
{
	cout << "function-try-block caught: '" << e.what() << "'" << endl;
}

int main()
{
	try {
		MyClass m;
	} catch (const exception& e) {
		cout << "main() caught: '" << e.what() << "'" << endl;
	}
	return 0;
}
