#include <iostream>
#include <string>

using namespace std;

string readName(istream& inStream);

int main()
{
	cout << "Reading a name from cin. You can usually close cin with Control-D (Control-Z in Windows): ";
	string theName = readName(cin);

	cout << "The name is \"" << theName << "\"" << endl;

	return 0;
}

/*
string readName(istream& inStream)
{
	string name;
	while (!inStream.fail()) {
		int next = inStream.get();
		if (next == std::char_traits<char>::eof())
			break;
		name += static_cast<char>(next);// Append character.
	}
	return name;
}
*/

string readName(istream& inStream)
{
	string name;
	char next;
	while (inStream.get(next)) {
		name += next;
	}

	return name;
}
