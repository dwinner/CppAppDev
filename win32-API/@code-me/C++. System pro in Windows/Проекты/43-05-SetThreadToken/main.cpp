#include <windows.h>
#include <stdio.h>

volatile UINT count;
volatile BOOL flag = TRUE;

void thread()
{
  while(flag)
  {
    count++;
    printf("count = %u\n", count);
    Sleep(500);
  }
}

int main()
{
  HANDLE hThread;
  DWORD IDThread;

  HANDLE hProcess;     // ���������� ��������
  HANDLE hToken;       // ���������� ������� �������
  HANDLE hDuplicate;   // ���������� ��������� ������� �������

  DWORD dwRetCode;     // ��� ��������

  // ��������� �����
  hThread = CreateThread(
    NULL,          // ������ �� ���������
    0,             // ������ ����� �� ���������
    (LPTHREAD_START_ROUTINE)thread,  // ����� ��������� ������
    NULL,          // ���������� ���
    CREATE_SUSPENDED,    // ����������� ��������� ������
    &IDThread);    // ������������� ������
  if (hThread == NULL)
  {
    printf("Create thread failed.\n");
    return GetLastError();
  }

  // �������� ���������� ��������
  hProcess = GetCurrentProcess();
  
  // �������� ������ ������� ������
  if (!OpenProcessToken(
    hProcess,          // ���������� ��������
    TOKEN_DUPLICATE,   // ������������ ������� �������
    &hToken))          // ���������� �������
  {
    dwRetCode = GetLastError();
    printf( "Open process token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // ��������� ������ �������
  if (!DuplicateToken(
    hToken,                  // ������ �������
    SecurityImpersonation,   // ������� ���������
    &hDuplicate))            // ����� ��������� ������� �������
  {
    dwRetCode = GetLastError();
    printf( "Duplicate token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // ������������� ���������� ������ ������� ��� ������
  if (!SetThreadToken(
    &hThread,      // ����� ����������� ������
    hDuplicate))   // �������� ������� �������
  {
    dwRetCode = GetLastError();
    printf( "Set thread token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  printf("Press any key to exit.\n");

  // ������������ �����
  ResumeThread(hThread);

  // ���� ������� �� ���������� ������
  getchar();

  flag = FALSE;    // ��������� �����

  CloseHandle(hThread);
  CloseHandle(hToken);

  return 0;
}