#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

bool isEven(int num)
{
	return num % 2 == 0;
}

int main()
{
	vector<int> vec(10);
	iota(begin(vec), end(vec), 0);

	function<bool(int)> f2 = isEven;
	int cnt = count_if(cbegin(vec), cend(vec), f2);
	cout << cnt << " even numbers" << endl;

	return 0;
}

