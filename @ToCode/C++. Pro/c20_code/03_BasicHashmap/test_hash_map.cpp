#include "hash_map.h"
#include <iostream>
#include <map>

using namespace ProCpp;
using namespace std;

int main()
{
	hash_map<int, int> myHash;
	myHash.insert(make_pair(4, 40));
	myHash.insert(make_pair(6, 60));

	// x will have type hash_map<int, int>::value_type*
	auto x = myHash.find(4);
	if (x != nullptr) {
		cout << "4 maps to " << x->second << endl;
	} else {
		cout << "cannot find 4 in map" << endl;
	}

	myHash.erase(4);

	auto x2 = myHash.find(4);
	if (x2 != nullptr) {
		cout << "4 maps to " << x2->second << endl;
	} else {
		cout << "cannot find 4 in map" << endl;
	}

	myHash[4] = 35;
	myHash[4] = 60;

	auto x3 = myHash.find(4);
	if (x3 != nullptr) {
		cout << "4 maps to " << x3->second << endl;
	} else {
		cout << "cannot find 4 in map" << endl;
	}


	hash_map<int, int> myHash2;
	myHash2 = myHash;
	hash_map<int, int> myHash3(myHash2);

	return 0;
}
