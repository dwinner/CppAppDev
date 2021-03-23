#include <windows.h>
#include <iostream.h>

int main()
{
  // удалаем каталог
  if (!RemoveDirectory("C:\\demo_dir"))
  {
    cerr << "Remove directory failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }

  cout << "The directory is removed." << endl;

  return 0;
}