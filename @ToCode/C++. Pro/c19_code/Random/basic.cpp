#include <iostream>
#include <random>

using namespace std;

int main()
{
	random_device rndDevice;
	mt19937 eng(rndDevice());
	uniform_int_distribution<int> dist(1, 99);
	cout << dist(eng) << endl;

	return 0;
}

