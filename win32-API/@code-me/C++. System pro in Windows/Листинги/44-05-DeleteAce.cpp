#include <windows.h>
#include <stdio.h>

int main()
{
  char chDirName[248];  // ��� �����

  PSECURITY_DESCRIPTOR lpSd = NULL;  // ��������� �� SD
  
  PACL lpDacl = NULL;    // ��������� �� ������ ���������� ��������
  BOOL bDaclPresent;     // ������� ����������� ������ DACL
  BOOL bDaclDefaulted;   // ������� ������ DACL �� ���������
  
  void *lpAce = NULL;    // ��������� �� ������� ������
  
  DWORD dwLength;        // ����� ����������� ������������
  DWORD dwRetCode;       // ��� ��������
  
  // ������ ��� �����
  printf("Input a directory or file name: ");
  gets(chDirName);
  
  // �������� ����� ����������� ������������
  if (!GetFileSecurity(
    chDirName,         // ��� �����
    DACL_SECURITY_INFORMATION,   // �������� DACL
    lpSd,              // ����� ����������� ������������
    0,                 // ���������� ����� ������
    &dwLength))        // ����� ��� ��������� �����
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
      // ������������ ������ ��� ������
      lpSd = (SECURITY_DESCRIPTOR*) new char[dwLength];
    else
    {
      // ������� �� ���������
      printf("Get file security failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
  }
  
  // ������������ ������ ��� ����������� ������������
  lpSd = (PSECURITY_DESCRIPTOR) new char[dwLength];
  
  // ������ ���������� ������������
  if (!GetFileSecurity(
    chDirName,     // ��� �����
    DACL_SECURITY_INFORMATION,   // �������� DACL
    lpSd,          // ����� ����������� ������������
    dwLength,      // ����� ������
    &dwLength))    // ����� ��� ��������� �����
  {
    dwRetCode = GetLastError();
    printf("Get file security failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // �������� ������ DACL �� ����������� ������������
  if (!GetSecurityDescriptorDacl(
    lpSd,              // ����� ����������� ������������
    &bDaclPresent,     // ������� ����������� ������ DACL
    &lpDacl,           // ����� ��������� �� DACL
    &bDaclDefaulted))  // ������� ������ DACL �� ���������
  {
    dwRetCode = GetLastError();
    printf("Get security descriptor DACL failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // ���������, ���� �� DACL
  if (!bDaclPresent)
  {
    printf("Dacl is not present.");

    return 0;
  }

  // ������� ����������� ������ �������� ������ DACL
  for (unsigned i = 0; i < lpDacl->AceCount; ++i)
  {
    // �������� ������� ������ DACL
    if (!GetAce(
      lpDacl,    // ����� DACL
      i,         // ������ ��������
      &lpAce))   // ��������� �� ������� ������
    {
      dwRetCode = GetLastError();
      printf("Get ace failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
    // ��������� ��� ��������
    if (((ACE_HEADER*)lpAce)->AceType == ACCESS_DENIED_ACE_TYPE)
      // ������� ������� �� ������ DACL
      if (!DeleteAce( lpDacl,  i))
      {
        dwRetCode = GetLastError();
        printf("Delete ace failed.\n");
        printf("Error code: %d\n", dwRetCode);
        
        return dwRetCode;
      }
  }
  // ������������� ����� ���������� ������������
  if (!SetFileSecurity(
    chDirName,                   // ��� �����
    DACL_SECURITY_INFORMATION,   // ������������� DACL
    lpSd))                       // ����� ����������� ������������
  {
    dwRetCode = GetLastError();
    printf("Set file security failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  printf("Denied elements are deleted from the DACL.\n");
  
  // ����������� ������
  delete[] lpSd;
  
  return 0;
}