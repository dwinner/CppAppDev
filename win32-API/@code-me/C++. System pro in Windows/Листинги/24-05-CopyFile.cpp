#include <windows.h>
#include <iostream.h>

int main()
{
  // копируем файл
  if(!CopyFile("C:\\demo_file.dat", "C:\\new_file.dat", FALSE))
  {
    cerr << "Copy file failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();
    return 0;
  }

  cout << "The file is copied." << endl;

  return 0;
}