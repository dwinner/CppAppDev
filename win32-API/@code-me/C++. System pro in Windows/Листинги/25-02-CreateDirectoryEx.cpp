#include <windows.h>
#include <iostream.h>

int main()
{
  // создаем подкаталог
  if (!CreateDirectoryEx("C:\\demo_dir", "C:\\demo_dir\\demo_subdir", NULL))
  {
    cerr << "Create directory failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }

  cout << "The subdirectory is created." << endl;

  return 0;
}