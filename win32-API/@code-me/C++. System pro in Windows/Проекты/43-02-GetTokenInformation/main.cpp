#include <windows.h>
#include <stdio.h>

int main()
{
  HANDLE hProcessToken;      // ���������� ������� �������
  PTOKEN_PRIVILEGES lpTokenPrivileges = NULL;
  
  LPTSTR lpPrivName = NULL;          // ����� ����� ����������
  LPTSTR lpPrivDisplayName = NULL;   // ����� ����� ���������� ��� 
                                     // �����������

  DWORD dwLangId;
  DWORD dwLength;
  
  DWORD dwRetCode;      // ��� ��������
  
  if (!OpenProcessToken(
    GetCurrentProcess(),     // ���������� ��������
    TOKEN_QUERY,             // ������ ���������� �� ������� �������
    &hProcessToken ))        // ���������� ������� �������
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor owner failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // �������� ����� ������ ��� ����������
  if (!GetTokenInformation(
    hProcessToken,       // ���������� ������� �������
    TokenPrivileges,     // �������� ����������
    lpTokenPrivileges,   // ����� ������
    0,                   // ����� ������
    &dwLength))          // ��������� �����
  {
    dwRetCode = GetLastError();
    if (dwRetCode != ERROR_INSUFFICIENT_BUFFER)
    {
      perror("Get token information for length failed.\n");
      printf("The last error code: %u\n", dwRetCode);
      
      return dwRetCode;
    }
    
    // ����������� ������ ��� ����� ����������
    lpTokenPrivileges = (TOKEN_PRIVILEGES*)new char[dwLength];
  }
  
  // �������� ���������� ������� �������
  if (!GetTokenInformation(
    hProcessToken,       // ���������� ������� �������
    TokenPrivileges,     // �������� ����������
    lpTokenPrivileges,   // ����� ������
    dwLength,            // ����� ������
    &dwLength))          // ��������� �����
  {
    dwRetCode = GetLastError();
    perror("Get token information failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // ������������� ����������
  printf( "User privileges: \n" );
  for( unsigned i = 0; i < lpTokenPrivileges->PrivilegeCount; ++i)
  {
    // �������� ��������� ����������
    if ((lpTokenPrivileges->Privileges[i].Attributes & 
        SE_PRIVILEGE_ENABLED) == SE_PRIVILEGE_ENABLED)
      printf("SE_PRIVILEGE_ENABLED:\n");
    if ((lpTokenPrivileges->Privileges[i].Attributes & 
        SE_PRIVILEGE_ENABLED_BY_DEFAULT) == 
        SE_PRIVILEGE_ENABLED_BY_DEFAULT)
      printf("SE_PRIVILEGE_ENABLED_BY_DEFAULT:\n");
    if ((lpTokenPrivileges->Privileges[i].Attributes & 
        SE_PRIVILEGE_USED_FOR_ACCESS) == SE_PRIVILEGE_USED_FOR_ACCESS)
      printf("SE_PRIVILEGE_USED_FOR_ACCESS:\n");
    if (!lpTokenPrivileges->Privileges[i].Attributes)
      printf("The privilege is disabled:\n");

    // ���������� ����� ����� ����������
    dwLength = 0;
    if (!LookupPrivilegeName(
      NULL,        // ��������� ������
      &(lpTokenPrivileges->Privileges[i].Luid),  // ����� LUID
      lpPrivName,  // ����� ����� ����������
      &dwLength))  // ����� ����� ������
    {
      dwRetCode = GetLastError();
      if (dwRetCode != ERROR_INSUFFICIENT_BUFFER)
      {
        perror("Lookup privilege name for length failed.\n");
        printf("The last error code: %u\n", dwRetCode);
        
        return dwRetCode;
      }
      
      // ����������� ������ ��� ����� ����������
      lpPrivName = new char[dwLength + 1];
    }
    
    // ���������� ��� ����������
    if (!LookupPrivilegeName(
      NULL,        // ��������� ������
      &(lpTokenPrivileges->Privileges[i].Luid),  // ����� LUID
      lpPrivName,  // ����� ����� ����������
      &dwLength))  // ����� ����� ������
    {
      dwRetCode = GetLastError();
      perror("Lookup privilege name failed.\n");
      printf("The last error code: %u\n", dwRetCode);
      
      return dwRetCode;
    }
    // ���������� ����� ����� ���������� ��� �����������
    dwLength = 0;
    if (!LookupPrivilegeDisplayName (
      NULL,          // ��������� ������
      lpPrivName,    // ��� ����������
      lpPrivDisplayName,   // ����� ��� ����� ����������
      &dwLength,     // ����� ����� ������
      &dwLangId))    // ����� �������������� �����
    {
      dwRetCode = GetLastError();
      if (dwRetCode != ERROR_INSUFFICIENT_BUFFER)
      {
        perror("Lookup privilege display name for length failed.\n");
        printf("The last error code: %u\n", dwRetCode);
        
        return dwRetCode;
      }
      
      // ����������� ������ ��� ����� ����������
      lpPrivDisplayName = new char[dwLength + 1];
    }
    
    // ���������� ��� ���������� ��� �����������
    if (!LookupPrivilegeDisplayName (
      NULL,          // ��������� ������
      lpPrivName,    // ��� ����������
      lpPrivDisplayName,   // ����� ��� ����� ����������
      &dwLength,     // ����� ����� ������
      &dwLangId))    // ����� �������������� �����
    {
      dwRetCode = GetLastError();
      perror("Lookup privilege display name failed.\n");
      printf("The last error code: %u\n", dwRetCode);
      
      return dwRetCode;
    }
    
    // ������������� ��� ���������� � ������������� �����
    printf("\t%s\n", lpPrivDisplayName);

    // ����������� ������
    delete[] lpPrivName;
    delete[] lpPrivDisplayName;

    lpPrivName = NULL;
    lpPrivDisplayName = NULL;
  }

  CloseHandle(hProcessToken);

  return 0;
}