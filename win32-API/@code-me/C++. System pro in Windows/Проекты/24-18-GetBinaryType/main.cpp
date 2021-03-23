#include <windows.h>
#include <iostream.h>

int main()
{
  DWORD  dwBinaryType;

  // определяем тип файла
  if(!GetBinaryType("C:\\temp.exe", &dwBinaryType))
  {
    cerr << "Get binary type failed." << endl
      << "The file may not be executable." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish.";
    cin.get();

    return 0;
  }

  // распечатываем тип файла
  if (dwBinaryType == SCS_32BIT_BINARY)
    cout << "The file is Win32 based application." << endl;
  else
    cout << "The file is not Win32 based application." << endl;

  return 0;
}