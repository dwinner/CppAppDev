#include <windows.h>
#include <stdio.h>
#include <lm.h>

int main()
{

  char chDirName[248];       // ��� ��������
  SECURITY_DESCRIPTOR sd;    // ���������� ������������ ��������
  SECURITY_ATTRIBUTES sa;    // �������� ������ ��������
  DWORD dwErrCode;           // ��� ��������

  // �������������� ������ ����������� ������������
  if (!InitializeSecurityDescriptor(
    &sd,
    SECURITY_DESCRIPTOR_REVISION))
  {
    dwErrCode = GetLastError();
    printf("Initialize security descroptor failed.\n");
    printf("Error code: %d\n", dwErrCode);

    return dwErrCode;
  }

  // ������������� SID ��������� �������
  if (!SetSecurityDescriptorOwner(
    &sd,         // ����� ����������� ������������
    NULL,        // �� ������ ���������
    SE_OWNER_DEFAULTED))  // ���������� ��������� �� ���������
  {
    dwErrCode = GetLastError();
    perror("Set security descriptor owner failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ������������� SID ��������� ������ ���������
  if (!SetSecurityDescriptorGroup(
    &sd,         // ����� ����������� ������������
    NULL,        // �� ������ ��������� ������
    SE_GROUP_DEFAULTED))  // ���������� ��������� ������ �� ���������
  {
    dwErrCode = GetLastError();
    perror("Set security descriptor group failed.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // ��������� ��������� ����������� ������������
  if (!IsValidSecurityDescriptor(&sd))
  {
    dwErrCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  // �������������� �������� ������������
  sa.nLength = sizeof(sa);   // ������������� ����� ��������� ������
  sa.lpSecurityDescriptor = &sd;   // ������������� ����� SD
  sa.bInheritHandle = FALSE;       // ���������� �������� �� �����������
  
  printf("Input a directory name: ");
  scanf("%s", chDirName);          // ������ ��� ��������

  // ������� �������
  if (!CreateDirectory(chDirName, &sa))
  {
    dwErrCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwErrCode);

    return dwErrCode;
  }

  printf("The directory is created.\n");

  return 0;
}