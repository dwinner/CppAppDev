#define _WIN32_WINNT 0x0500

#ifndef PROTECTED_DACL_SECURITY_INFORMATION
#define PROTECTED_DACL_SECURITY_INFORMATION  0x80000000L
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>
#include <aclapi.h>
#include <sddl.h>

int main()
{
  char chFileName[256];    // ��� �����
  HANDLE hFile;            // ���������� �����

  PSECURITY_DESCRIPTOR pSecurityDescriptor;  // ��������� �� SD
  PACL pDacl;          // ��������� �� DACL

  DWORD dwRetCode;    // ��� ��������

  // ������ ������ ��� �����, ��������: C:\\test.txt
  printf("Input a full path to your file: ");
  gets(chFileName);

  // ��������� ����
  hFile = CreateFile(
    chFileName,      // ��� �����
    READ_CONTROL | WRITE_DAC,  // ������ � ����������� ������������
    0,               // �� ��������� ������
    NULL,            // �� ����������� ����������
    OPEN_EXISTING,   // ��������� ������������ ����
    FILE_ATTRIBUTE_NORMAL,   // ������� ����
    NULL);           // ������� ���
  if(hFile == INVALID_HANDLE_VALUE)
  {
    dwRetCode = GetLastError();
    printf("Create file failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // �������� ���������� ������������ �����
  dwRetCode = GetSecurityInfo(
    hFile,           // ���������� �����
    SE_FILE_OBJECT,  // ������ ����
    DACL_SECURITY_INFORMATION,   // ��� ����������
    NULL,            // ��������� �� SID ��������� �� �����
    NULL,            // ��������� �� ��������� ������ �� �����
    &pDacl,          // ��������� �� DACL
    NULL,            // ��������� �� SACL �� �����
    &pSecurityDescriptor);   // ����� ��������� �� SD
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Get named security info failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ���������� ���� ��������������� ������������ DACL
  if(!SetSecurityDescriptorControl(
    pSecurityDescriptor,
    SE_DACL_PROTECTED,
    0))
  {
    dwRetCode = GetLastError();
    printf("Set security descriptor control failed.");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ������������� ����� �������� DACL
  dwRetCode = SetSecurityInfo(
    hFile,         // ���������� �����
    SE_FILE_OBJECT,    // ������ ����
    DACL_SECURITY_INFORMATION | 
    PROTECTED_DACL_SECURITY_INFORMATION,   // �������� ���������� � DACL
    NULL,          // ��������� �� ��������
    NULL,          // ��������� ������ �� ��������
    pDacl,         // DACL ��������
    NULL);         // SACL �� ��������
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Set named security info failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ����������� ������ ��� �����������
  LocalFree(pSecurityDescriptor);

  printf("The flag SE_DACL_PROTECTED is reset.\n");

  // ��������� ����
  CloseHandle(hFile);

  return 0;
}