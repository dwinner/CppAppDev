#include <random>
#include <functional>
#include <map>
#include <fstream>

using namespace std;

int main()
{
	const unsigned int DIST_START = 1;
	const unsigned int DIST_END = 99;
	const unsigned int ITERATIONS = 1000000;

	// Uniform Mersenne Twister
	random_device rndDevice;
	mt19937 eng(rndDevice());
	uniform_int_distribution<int> dist(DIST_START, DIST_END);
	auto gen = bind(dist, eng);
	map<int, int> m;
	for (unsigned int i = 0; i < ITERATIONS; ++i) {
		int rnd = gen();
		// Search map for a key = rnd. If found, add 1 to the value associated
		// with that key. If not found, add the key to the map with value 1.
		++(m[rnd]);
	}

	// Write to a CSV file
	ofstream of("res.csv");
	for (unsigned int i = DIST_START; i <= DIST_END; ++i) {
		of << i << ",";
		auto res = m.find(i);
		of << (res != end(m) ? res->second : 0) << endl;
	}

	return 0;
}
