#include <windows.h>
#include <iostream.h>
#include <string.h>

int main()
{
  HANDLE  hMailslot;
  char  mailslotName[] = "\\\\.\\mailslot\\demo_mailslot";
  
  // ����������� � �������� ������
  hMailslot = CreateFile(
    mailslotName,      // ��� ��������� �����
    GENERIC_WRITE,     // ���������� � ����
    FILE_SHARE_READ,   // ��������� ������������� ������ �� �����
    NULL,              // ������ �� ���������
    OPEN_EXISTING,     // ��������� ������������ �����
    0,                 // �������� �� ���������
    NULL               // �������������� ��������� ���
    );
  
  // ��������� ����� � �������� ������
  if (hMailslot == INVALID_HANDLE_VALUE)
  {
    cerr << "Create file failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to finish the client.";
    cin.get();
    
    return 0;
  }
  
  // ������ ���������� ������������ ���������
  int  n;
  cout << "Input a number of messages: ";
  cin >> n;
  cin.get();
  
  // ����� ��������� � �������� ����
  for (int i = 0; i < n; ++i)
  {
    DWORD  dwBytesWritten;
    char  pchMessage[256];
    int    nMessageSize;
    
    cout << "Input message: ";
    // ������ ���������
    cin.getline(pchMessage, 256);
    // ��������� ����� ���������
    nMessageSize = strlen(pchMessage) + 1;
    
    // ����� ���������
    if (!WriteFile(
      hMailslot,       // ���������� ��������� �����
      pchMessage,      // ������
      nMessageSize,    // ������ ������
      &dwBytesWritten, // ���������� ���������� ������
      NULL             // ���������� ������
      ))
    {
      // ������ ������
      cerr << "Write file failed: " << endl
        << "The last error code: " << GetLastError() << endl;
      cout << "Press any key to finish the client.";
      cin.get();
      
      CloseHandle(hMailslot);

      return 0;
    }
  }
  
  // ��������� ���������� ������
  CloseHandle(hMailslot);
  // ��������� �������
  cout << "The messages are written by the client." << endl
    << "Press any key to exit." << endl;
  cin.get();
  
  return 0;
}