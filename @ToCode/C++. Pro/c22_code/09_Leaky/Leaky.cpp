class Simple 
{
public:
	Simple() { mIntPtr = new int(); }
	virtual ~Simple() { delete mIntPtr; }

	void setIntPtr(int inInt) { *mIntPtr = inInt; }

private:
	int* mIntPtr;
};

void doSomething(Simple*& outSimplePtr)
{
	outSimplePtr = new Simple(); // BUG! Doesn't delete the original.
}

int main()
{
	Simple* simplePtr = new Simple(); // Allocate a Simple object.

	doSomething(simplePtr);

	delete simplePtr; // Only cleans up the second object.

	return 0;
}
