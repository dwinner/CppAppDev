#include <windows.h>
#include <iostream.h>

int main()
{
  // создаем каталог
  if (!CreateDirectory("C:\\demo_dir", NULL))
  {
    cerr << "Create directory failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }

  cout << "The directory is created." << endl;

  return 0;
}