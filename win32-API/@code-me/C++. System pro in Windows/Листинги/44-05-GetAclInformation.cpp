#include <windows.h>
#include <stdio.h>

int main()
{
  char chDirName[248];   // имя файла
  
  PSECURITY_DESCRIPTOR lpSd = NULL;  // указатель на SD
  
  PACL lpDacl = NULL;    // указатель на список управления доступом
  BOOL bDaclPresent;     // признак присутствия списка DACL     
  BOOL bDaclDefaulted;   // признак списка DACL по умолчанию
  
  ACL_REVISION_INFORMATION ari;  // версия списка DACL
  ACL_SIZE_INFORMATION asi;      // размер списка DACL

  DWORD dwLength;      // длина дескриптора безопасности

  DWORD dwRetCode;     // код возврата
  
  // вводим имя файла
  printf("Input a directory or file name: ");
  gets(chDirName);
  
  // получаем длину дескриптора безопасности
  if (!GetFileSecurity(
    chDirName,         // имя файла
    DACL_SECURITY_INFORMATION,   // получаем DACL
    lpSd,              // адрес дескриптора безопасности
    0,                 // определяем длину буфера
    &dwLength))        // адрес для требуемой длины
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
      // распределяем память для буфера
      lpSd = (SECURITY_DESCRIPTOR*) new char[dwLength];
    else
    {
      // выходим из программы
      printf("Get file security failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
  }
  
  // распределяем память для дескриптора безопасности
  lpSd = (PSECURITY_DESCRIPTOR) new char[dwLength];
  
  // читаем дескриптор безопасности
  if (!GetFileSecurity(
    chDirName,         // имя файла
    DACL_SECURITY_INFORMATION,   // получаем DACL
    lpSd,              // адрес дескриптора безопасности
    dwLength,          // длину буфера
    &dwLength))        // адрес для требуемой длины
  {
    dwRetCode = GetLastError();
    printf("Get file security failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // получаем список DACL из дескриптора безопасности
  if (!GetSecurityDescriptorDacl(
    lpSd,              // адрес дескриптора безопасности
    &bDaclPresent,     // признак присутствия списка DACL
    &lpDacl,           // адрес указателя на DACL
    &bDaclDefaulted))  // признак списка DACL по умолчанию
  {
    dwRetCode = GetLastError();
    printf("Get security descriptor DACL failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // проверяем, есть ли DACL
  if (!bDaclPresent)
  {
    printf("Dacl is not present.");

    return 0;
  }
  
  // получаем версию списка DACL
  GetAclInformation(
    lpDacl,        // адрес DACL
    &ari,          // адрес буфера
    sizeof(ari),   // размер буфера
    AclRevisionInformation);   // информация о версии

  // печатаем версию списка DACL
  printf("Acl Revision Information: %u\n", ari.AclRevision);

  // получаем размеры списка DACL
  GetAclInformation(
    lpDacl,        // адрес DACL
    &asi,          // адрес буфера
    sizeof(asi),   // размер буфера
    AclSizeInformation);   // информация о размерах DACL

  // печатаем информацию о размерах списка DACL
  printf("Ace Count: %u\n", asi.AceCount);
  printf("AclBytesInUse: %u\n", asi.AclBytesInUse);
  printf("Acl Bytes Free: %u\n", asi.AclBytesFree);

  // освобождаем память
  delete[] lpSd;
  
  return 0;
}