#include <cstddef>
#include <iostream>
#include <cstring>

using namespace std;

static const size_t NOT_FOUND = (size_t)(-1);

template <typename T>
size_t Find(T& value, T* arr, size_t size)
{
	cout << "original" << endl;
	for (size_t i = 0; i < size; i++) {
		if (arr[i] == value) {
			return i; // found it; return the index
		}
	}
	return NOT_FOUND; // Failed to find it; return NOT_FOUND
}

template <typename T, size_t S>
size_t Find(T& value, T(&arr)[S])
{
	return Find(value, arr, S);
}

size_t Find(const char*& value, const char** arr, size_t size)
{
	cout << "overload" << endl;
	for (size_t i = 0; i < size; i++) {
		if (strcmp(arr[i], value) == 0) {
			return i; // found it; return the index
		}
	}
	return NOT_FOUND; // Failed to find it; return NOT_FOUND
}

int main()
{
	const char* word = "two";
	const char* arr[] = { "one", "two", "three", "four" };
	size_t sizeArr = sizeof(arr) / sizeof(arr[0]);
	size_t res;
	res = Find<const char*>(word, arr, sizeArr); // Calls template with T=const char*
	res = Find(word, arr, sizeArr);              // Calls non-template function.
	if (res != NOT_FOUND)
		cout << res << endl;
	else
		cout << "Not found" << endl;

	return 0;
}
