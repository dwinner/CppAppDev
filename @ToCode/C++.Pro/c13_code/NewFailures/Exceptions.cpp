#include <iostream>
#include <limits>

using namespace std;

int main()
{
	int* ptr;
	int numInts = numeric_limits<int>::max();

	try {
		ptr = new int[numInts];
	} catch (const bad_alloc& e) {
		cerr << __FILE__ << "(" << __LINE__ << "): Unable to allocate memory: " << e.what() << endl;
		// Handle memory allocation failure
		return 1;
	}
	// Proceed with function that assumes memory has been allocated

	return 0;
}
