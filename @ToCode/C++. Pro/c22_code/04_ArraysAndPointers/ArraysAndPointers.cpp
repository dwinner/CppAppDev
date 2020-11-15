#include <cstddef>

void doubleInts(int* theArray, size_t inSize)
{
	for (size_t i = 0; i < inSize; i++) {
		theArray[i] *= 2;
	}
}

/*
void doubleInts(int theArray[], size_t inSize)
{
	for (size_t i = 0; i < inSize; i++) {
		theArray[i] *= 2;
	}
}
*/

/*
void doubleIntsStack(int (&theArray)[4])
{
	for (size_t i = 0; i < 4; i++) {
		theArray[i] *= 2;
	}
}
*/

template<size_t N>
void doubleIntsStack(int (&theArray)[N])
{
	for (size_t i = 0; i < N; i++) {
		theArray[i] *= 2;
	}
}

int main()
{
	size_t arrSize = 4;
	int* heapArray = new int[arrSize]{ 1, 5, 3, 4 };
	doubleInts(heapArray, arrSize);
	//doubleIntsStack(heapArray);	// Does not work.
	delete[] heapArray;
	heapArray = nullptr;

	int stackArray[] = { 5, 7, 9, 11 };
	arrSize = sizeof(stackArray) / sizeof(stackArray[0]);
	doubleInts(stackArray, arrSize);
	doubleInts(&stackArray[0], arrSize);

	doubleIntsStack(stackArray);

	return 0;
}
