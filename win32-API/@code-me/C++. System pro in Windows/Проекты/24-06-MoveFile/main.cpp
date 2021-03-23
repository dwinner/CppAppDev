#include <windows.h>
#include <iostream.h>

int main()
{
  // ןונולושאול פאיכ
  if(!MoveFile("C:\\demo_file.dat", "C:\\new_file.dat"))
  {
    cerr << "Move file failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();
    return 0;
  }

  cout << "The file is moved." << endl;

  return 0;
}