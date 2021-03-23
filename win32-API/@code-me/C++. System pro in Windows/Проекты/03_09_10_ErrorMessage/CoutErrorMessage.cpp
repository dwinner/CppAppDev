#include <windows.h>
#include <iostream.h>

void CoutErrorMessage()
{
  char prefix[] = "������ Win32 API: ";
  LPVOID lpMsgBuf;

  CharToOem(prefix,prefix);  // ������������ ���������

  FormatMessage( 
    FORMAT_MESSAGE_ALLOCATE_BUFFER | 
    FORMAT_MESSAGE_FROM_SYSTEM | 
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    GetLastError(),
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // ���� �� ���������
    (LPTSTR) &lpMsgBuf,
    0,
    NULL 
  );
  // ������������ ������� �����
  CharToOem((char*)lpMsgBuf,(char*)lpMsgBuf);
  // ������� ��������� �� ������ �� �������
  cout << prefix << (char*)lpMsgBuf << endl;
  // ����������� �����
  LocalFree(lpMsgBuf);
}