import std;

using namespace std;

vector<int> ReadIntegerFile(const string& filename)
{
	ifstream inputStream{ filename };
	if (inputStream.fail())
	{
		// We failed to open the file: throw an exception.
		throw exception{};
	}

	// Read the integers one-by-one and add them to a vector.
	vector<int> integers;
	int temp;
	while (inputStream >> temp)
	{
		integers.push_back(temp);
	}		

	return integers;
}

int main()
{
	const string filename{ "IntegerFile.txt" };
	vector<int> myInts;

	try
	{
		myInts = ReadIntegerFile(filename);
	}
	catch (const exception& /* e */)
	{
		println(cerr, "Unable to open file {}", filename);
		return 1;
	}	

	for (const auto& intItem : myInts)
	{
		print("{} ", intItem);
	}
	
	println("");	
}
