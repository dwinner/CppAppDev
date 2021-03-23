#include <windows.h>
#include <stdio.h>

int main()
{
  HANDLE hProcess;       // ���������� ��������
  HANDLE hTokenHandle;   // ���������� ������� �������

  TOKEN_SOURCE ts;       // �������� ������� �������

  DWORD dwRetLength;     // ������������ ����� ������
  DWORD dwRetCode;       // ��� ��������

  // �������� ���������� ��������
  hProcess = GetCurrentProcess();

  // ��������� ������ ������� ��������
  if (!OpenProcessToken(
    hProcess,            // ���������� ��������
    TOKEN_QUERY_SOURCE,  // ������ � ��������� �������
    &hTokenHandle))      // ���������� �������
  {
    dwRetCode = GetLastError();
    printf( "Open process token failed: %u\n", dwRetCode);

    return dwRetCode;
  }

  // �������� �������� ������� �������
  if (!GetTokenInformation(
    hTokenHandle,    // ���������� ������� �������
    TokenSource,     // �������� �������� ������� �������
    &ts,             // ����� ������ ��� ���������
    sizeof(ts),      // ������ ������
    &dwRetLength))   // ��������� ������ ������ � ������ �������
  {
    dwRetCode = GetLastError();
    printf( "Get token information failed: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ������������� �������� ������� �������
  printf("Source name: ");
  for (int i = 0; i < TOKEN_SOURCE_LENGTH; ++i)
    putchar(ts.SourceName[i]);
  putchar('\n');
  printf("Source identifier: %X %X\n", ts.SourceIdentifier.HighPart,
    ts.SourceIdentifier.LowPart);

  CloseHandle(hTokenHandle);

  return 0;
}