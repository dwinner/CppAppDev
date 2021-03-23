#include <windows.h>
#include <iostream.h>
#include <string.h>

int main()
{
  HANDLE   hNamedPipe;
  SECURITY_ATTRIBUTES sa;    // �������� ������������
  SECURITY_DESCRIPTOR sd;    // ���������� ������������
  
  // ������������� ��������� ������������
  sa.nLength = sizeof(sa);
  sa.bInheritHandle = FALSE;   // ���������� ������ �������������
  // �������������� ���������� ������������
  InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
  // ��������� ������ � ������������ ������ ���� �������������
  SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
  sa.lpSecurityDescriptor = &sd;

  // ������� ����������� ����� ��� ������ � ������
  hNamedPipe = CreateNamedPipe(
    "\\\\.\\pipe\\demo_pipe",      // ��� ������
    PIPE_ACCESS_DUPLEX,    // ������ �� ������ � ����� � �����
    PIPE_TYPE_MESSAGE | PIPE_WAIT, // ���������� �������� ���������
    1,         // ������������ ���������� ����������� ������ 
    0,         // ������ ��������� ������ �� ���������
    0,         // ������ �������� ������ �� ���������
    INFINITE,  // ������ ���� ����� ���������� �����
    &sa        // ������ ��� ���� �������������
    );
  // ��������� �� �������� ��������
  if (hNamedPipe == INVALID_HANDLE_VALUE)
  {
    cerr << "Create named pipe failed." << endl
      << "The last error code: " << GetLastError() << endl;
    cout << "Press any key to exit.";
    cin.get();
    
    return 0;
  }
  
  // ����, ���� ������ �������� � �������
  cout << "The server is waiting for connection with a client." << endl;
  if(!ConnectNamedPipe(
    hNamedPipe,  // ���������� ������
    NULL         // ����� ����������
    ))
  {
    cerr << "Connect named pipe failed." << endl
      << "The last error code: "<<GetLastError() << endl;
    CloseHandle(hNamedPipe);
    cout << "Press any key to exit.";
    cin.get();
    
    return 0;
  }
  // ��������� �������
  cout << "Press any key to exit.";
  cin.get();
  // ��������� ���������� ������ 
  CloseHandle(hNamedPipe);
  
  return 0;
}