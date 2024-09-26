#include <iostream>
extern int start_program(int, const char **);
using namespace std;
int main()
{
  cout << "Test 1: Passing zero arguments to start_program:\n";
  auto exit_code = start_program(0, nullptr);
  if (exit_code == 0)
    cout << "Test FAILED: Unexpected zero exit code.\n";
  else
    cout << "Test PASSED: Non-zero exit code returned.\n";
  cout << endl;

  cout << "Test 2: Passing 2 arguments to start_program:\n";
  const char *arguments[2] = {"hello", "world"};
  exit_code = start_program(2, arguments);
  if (exit_code != 0)
    cout << "Test FAILED: Unexpected non-zero exit code\n";
  else
    cout << "Test PASSED\n";
}
