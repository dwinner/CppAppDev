#include <windows.h>
#include <stdio.h>

int main()
{
  LPTSTR lpPrivDisplayName = NULL;   // ����� ����� ���������� ��� �����������

  DWORD dwLength = 0;  // ����� ����� ����������
  DWORD dwLangId;      // ������������� �����

  DWORD dwRetCode;     // ��� ��������


  // ���������� ����� ����� ���������� ��� �����������
  if (!LookupPrivilegeDisplayName (
    NULL,              // ��������� ������
    SE_SHUTDOWN_NAME,  // ��� ����������
    lpPrivDisplayName,     // ����� ��� ����� ����������
    &dwLength,         // ����� ����� ������
    &dwLangId))        // ����� �������������� �����
  {
    dwRetCode = GetLastError();
    if (dwRetCode != ERROR_INSUFFICIENT_BUFFER)
    {
      perror("Lookup privilege display name failed.\n");
      printf("The last error code: %u\n", dwRetCode);

      return dwRetCode;
    }

    // ����������� ������ ��� ����� ����������
    lpPrivDisplayName = new char[dwLength + 1];
  }

  // ���������� ��� ���������� ��� �����������
  if (!LookupPrivilegeDisplayName (
    NULL,              // ��������� ������
    SE_SHUTDOWN_NAME,  // ��� ����������
    lpPrivDisplayName,     // ����� ��� ����� ����������
    &dwLength,         // ����� ����� ������
    &dwLangId))        // ����� �������������� �����
  {
    dwRetCode = GetLastError();
    perror("Lookup privilege display name failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ������������� ��� ���������� � ������������� �����
  printf("Display name of the privilege SE_SHUTDOWN_NAME:\n\t%s\n", lpPrivDisplayName);
  printf("Language identifier: %x\n", dwLangId);

  delete[] lpPrivDisplayName;

  return 0;
}