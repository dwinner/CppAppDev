#include <iostream>
#include <random>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

template<typename T>
void fillVector(vector<int>& vec, T rndGen)
{
	generate(begin(vec), end(vec), rndGen);
}

int main()
{
	random_device rndDevice;
	mt19937 eng(rndDevice());
	uniform_int_distribution<int> dist(1, 99);

	auto gen = std::bind(dist, eng);

	vector<int> vec(10);
	fillVector(vec, gen);

	for (auto i : vec) {
		cout << i << "  ";
	}
	cout << endl;

	return 0;
}

