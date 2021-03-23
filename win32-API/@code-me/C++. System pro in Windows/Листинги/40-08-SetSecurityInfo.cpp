#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h> 
#include <lm.h>
#include <aclapi.h>

int main()
{
  wchar_t wchFileName[256];    // ��� �����
  wchar_t wchUserName[UNLEN];  // ��� ������ ��������� �����

  HANDLE hFile;                // ���������� �����

  PSID lpSID = NULL;           // ��������� �� SID
  LPTSTR lpDomainName = NULL;  // ��������� �� ��� ������

  DWORD dwLengthOfSID = 0;     // ����� SID
  DWORD dwLengthOfDomainName = 0;  // ����� ����� ������

  DWORD dwRetCode;     // ��� ��������

  SID_NAME_USE typeOfSID;      // ��� ������� ������

  // ������ ��� �����, ��������: C:\\test.txt
  printf("Input a full path to your file: ");
  _getws(wchFileName);

  // ������ ��� ������ ��������� �������
  printf("Input a user name: ");
  wscanf(L"%s", wchUserName);

  // ��������� ����
  hFile = CreateFile(
    wchFileName,         // ��� �����
    WRITE_OWNER,         // ��������� ��������� ��������� �����
    0,                   // �� ��������� ������
    NULL,                // �� ����������� ����������
    OPEN_EXISTING,       // ��������� ������������ ����
    FILE_ATTRIBUTE_NORMAL,   // ������� ����
    NULL);               // ������� ���
  if(hFile == INVALID_HANDLE_VALUE)
  {
    dwRetCode = GetLastError();
    printf("Create file failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  // ���������� ����� SID ������ ��������� �����
  LookupAccountName(
    NULL,              // ���� ��� �� ��������� ����������
    wchUserName,       // ��� ������ ��������� �����
    NULL,              // ���������� ����� SID
    &dwLengthOfSID,    // ����� SID
    NULL,              // ���������� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &typeOfSID);       // ��� ������� ������

  // ���������, ������� �� ������� ����� SID
  if (dwLengthOfSID == 0)
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // ������������ ������ ��� SID � ����� ������
  lpSID = (PSID) new wchar_t[dwLengthOfSID];
  lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];

  // ���������� SID � ��� ������ ������������
  if(!LookupAccountName(
    NULL,              // ���� ��� �� ��������� ����������
    wchUserName,       // ��� ������������
    lpSID,             // ��������� �� SID
    &dwLengthOfSID,    // ����� SID
    lpDomainName,      // ��������� �� ��� ������
    &dwLengthOfDomainName,   // ����� ����� ������
    &typeOfSID))       // ��� ������� ������
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }
 
  // ������������� ������ ��������� �����
  dwRetCode = SetSecurityInfo(
    hFile,           // ���������� �����
    SE_FILE_OBJECT,  // ������ ����
    OWNER_SECURITY_INFORMATION,  // �������� ������ ��� ��������� �����
    lpSID,           // ����� �� SID ������ ���������
    NULL,            // ��������� ������ �� ��������
    NULL,            // DACL �� ��������
    NULL);           // SACL �� ��������
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("Set named security info failed.\n");
    printf("Error code: %u\n", dwRetCode);

    return dwRetCode;
  }

  printf("The new owner of the file is set.\n");
  
  // ������������ ������
  delete[] lpSID;
  delete[] lpDomainName;

  // ��������� ����
  CloseHandle(hFile);

  return 0;
}