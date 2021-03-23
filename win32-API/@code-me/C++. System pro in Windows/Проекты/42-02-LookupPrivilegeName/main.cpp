#include <windows.h>
#include <stdio.h>

int main()
{
  LUID  luId;                // ��������� ������������� ��� ����������
  DWORD dwLength = 0;        // ����� ����� ����������
  LPTSTR lpPrivName = NULL;  // ����� ����� ����������

  DWORD dwRetCode;           // ��� ��������

  // ���������� ��������� ������������� ����������
  if (!LookupPrivilegeValue(
    NULL,            // ���� ���������� �� ��������� ������
    SE_DEBUG_NAME,   // ���������� ��������� ������� ��������
    &luId))          // ����� ���������� �������������� ����������
  {
    dwRetCode = GetLastError();
    perror("Lookup privilege value failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ������������� LUID
  printf("Luid of SE_DEBUG_NAME privilege. ");
  printf("High part: %x, Low part: %x\n", luId.HighPart, luId.LowPart);

  // ���������� ����� ����� ����������
  if (!LookupPrivilegeName(
    NULL,          // ��������� ������
    &luId,         // ����� ���������� ����������� ��������������
    lpPrivName,    // ����� ����� ����������
    &dwLength))    // ����� ����� ������
  {
    dwRetCode = GetLastError();
    if (dwRetCode != ERROR_INSUFFICIENT_BUFFER)
    {
      perror("Lookup privilege name failed.\n");
      printf("The last error code: %u\n", dwRetCode);

      return dwRetCode;
    }

    // ����������� ������ ��� ����� ����������
    lpPrivName = new CHAR[dwLength + 1];
  }

  // ���������� ��� ����������
  if (!LookupPrivilegeName(
    NULL,          // ��������� ������
    &luId,         // ����� ���������� ����������� ��������������
    lpPrivName,    // ����� ����� ����������
    &dwLength))    // ����� ����� ������
  {
    dwRetCode = GetLastError();
    perror("Lookup privilege name failed.\n");
    printf("The last error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ������������� ��� ����������
  printf("Name of the Luid: %s\n", lpPrivName);

  delete[] lpPrivName;

  return 0;
}