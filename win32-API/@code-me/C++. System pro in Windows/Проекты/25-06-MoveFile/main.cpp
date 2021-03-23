#include <windows.h>
#include <iostream.h>

int main()
{
  // перемещаем каталог
  if(!MoveFile("C:\\demo_dir", "C:\\new_dir"))
  {
    cerr << "Move file failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }

  cout << "The directory is moved." << endl;

  return 0;
}