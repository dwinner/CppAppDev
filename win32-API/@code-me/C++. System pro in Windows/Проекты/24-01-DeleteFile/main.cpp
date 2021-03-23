#include <windows.h>
#include <iostream.h>

int main()
{
  // удаляем файл
  if(!DeleteFile("C:\\demo_file.dat"))
  {
    cerr << "Delete file failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();
    return 0;
  }
  cout << "The file is deleted." << endl;

  return 0;
}