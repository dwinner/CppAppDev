import std;
import utils;

using namespace std;

int main()
{
   println("{}", Concat(1, 2.2));
	println("{}", Concat("Hello ", "World"));
	println("{}", Concat("Hello ", 1));
	println("{}", Concat(2, " World"));
}
