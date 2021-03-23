#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <windows.h> 
#include <aclapi.h>

int main()
{
  char chFileName[256];    // ��� �����
  HANDLE hFile;            // ���������� �����

  PSECURITY_DESCRIPTOR pSecurityDescriptor;  // ��������� �� SD

  SECURITY_DESCRIPTOR_CONTROL wControl;  // ����������� ����� �� SD
  DWORD dwRevision;      // ������ ����������� ������������

  DWORD dwRetCode;       // ��� ��������

  // ������ ������ ��� �����, ��������: C:\\test.txt
  printf("Input a full path to your file: ");
  gets(chFileName);

  // ��������� ����
  hFile = CreateFile(
    chFileName,        // ��� �����
    READ_CONTROL,      // ��������� ������ � ����������� ������������
    0,                 // �� ��������� ������
    NULL,              // �� ����������� ����������
    OPEN_EXISTING,     // ��������� ������������ ����
    FILE_ATTRIBUTE_NORMAL,   // ������� ����
    NULL);             // ������� ���
  if(hFile == INVALID_HANDLE_VALUE)
  {
    dwRetCode = GetLastError();
    printf("Create file failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // �������� ���������� ������������ �����
  dwRetCode = GetSecurityInfo(
    hFile,         // ���������� �����
    SE_FILE_OBJECT,    // ������ ����
    DACL_SECURITY_INFORMATION,   // ��� ����������
    NULL,          // ��������� �� SID ��������� �� �����
    NULL,          // ��������� �� ��������� ������ �� �����
    NULL,          // ��������� �� DACL �� �����
    NULL,          // ��������� �� SACL �� �����
    &pSecurityDescriptor);       // ����� ��������� �� SD
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // �������� ����������� ���������� �� ����������� ������������
  if(!GetSecurityDescriptorControl(
    pSecurityDescriptor,
    &wControl,
    &dwRevision))
  {
    dwRetCode = GetLastError();
    printf("Get security descriptor control failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("The following flags are set: \n");

  // ���������� ���������� �� ������������ �����
  if(wControl & SE_DACL_AUTO_INHERITED)
    printf("SE_DACL_AUTO_INHERITED\n");
  if(wControl & SE_DACL_DEFAULTED)
    printf("SE_DACL_DEFAULTED\n");
  if(wControl & SE_DACL_PRESENT)
    printf("SE_DACL_PRESENT\n");
  if(wControl & SE_DACL_PROTECTED)
    printf("SE_DACL_PROTECTED\n");

  // ������� �� ������ ������ ����������� ������������
  printf("Descriptor revision: %u\n", dwRevision);

  // ����������� ������ ��� �����������
  LocalFree(pSecurityDescriptor);

  // ��������� ����
  CloseHandle(hFile);

  return 0;
}