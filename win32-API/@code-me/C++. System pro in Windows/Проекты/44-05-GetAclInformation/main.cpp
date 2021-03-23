#include <windows.h>
#include <stdio.h>

int main()
{
  char chDirName[248];   // ��� �����
  
  PSECURITY_DESCRIPTOR lpSd = NULL;  // ��������� �� SD
  
  PACL lpDacl = NULL;    // ��������� �� ������ ���������� ��������
  BOOL bDaclPresent;     // ������� ����������� ������ DACL     
  BOOL bDaclDefaulted;   // ������� ������ DACL �� ���������
  
  ACL_REVISION_INFORMATION ari;  // ������ ������ DACL
  ACL_SIZE_INFORMATION asi;      // ������ ������ DACL

  DWORD dwLength;      // ����� ����������� ������������

  DWORD dwRetCode;     // ��� ��������
  
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
    chDirName,         // ��� �����
    DACL_SECURITY_INFORMATION,   // �������� DACL
    lpSd,              // ����� ����������� ������������
    dwLength,          // ����� ������
    &dwLength))        // ����� ��� ��������� �����
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
  
  // �������� ������ ������ DACL
  GetAclInformation(
    lpDacl,        // ����� DACL
    &ari,          // ����� ������
    sizeof(ari),   // ������ ������
    AclRevisionInformation);   // ���������� � ������

  // �������� ������ ������ DACL
  printf("Acl Revision Information: %u\n", ari.AclRevision);

  // �������� ������� ������ DACL
  GetAclInformation(
    lpDacl,        // ����� DACL
    &asi,          // ����� ������
    sizeof(asi),   // ������ ������
    AclSizeInformation);   // ���������� � �������� DACL

  // �������� ���������� � �������� ������ DACL
  printf("Ace Count: %u\n", asi.AceCount);
  printf("AclBytesInUse: %u\n", asi.AclBytesInUse);
  printf("Acl Bytes Free: %u\n", asi.AclBytesFree);

  // ����������� ������
  delete[] lpSd;
  
  return 0;
}