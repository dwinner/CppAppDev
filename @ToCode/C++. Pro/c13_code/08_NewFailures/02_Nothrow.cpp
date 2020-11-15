#include <cstddef>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
	int* ptr;
	size_t numInts = numeric_limits<int>::max();

	ptr = new(nothrow) int[numInts];
	if (ptr == nullptr) {
		cerr << __FILE__ << "(" << __LINE__ << "): Unable to allocate memory!" << endl;
		// Handle memory allocation failure
		return 1;
	}
	// Proceed with function that assumes memory has been allocated

	return 0;
}
