#include <windows.h>
#include <stdio.h>

int main()
{
  char chDirName[248];  // имя файла

  PSECURITY_DESCRIPTOR lpSd = NULL;  // указатель на SD
  
  PACL lpDacl = NULL;    // указатель на список управления доступом
  BOOL bDaclPresent;     // признак присутствия списка DACL
  BOOL bDaclDefaulted;   // признак списка DACL по умолчанию
  
  void *lpAce = NULL;    // указатель на элемент списка
  
  DWORD dwLength;        // длина дескриптора безопасности
  DWORD dwRetCode;       // код возврата
  
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
    chDirName,     // имя файла
    DACL_SECURITY_INFORMATION,   // получаем DACL
    lpSd,          // адрес дескриптора безопасности
    dwLength,      // длину буфера
    &dwLength))    // адрес для требуемой длины
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

  // удаляем запрещающие доступ элементы списка DACL
  for (unsigned i = 0; i < lpDacl->AceCount; ++i)
  {
    // получить элемент списка DACL
    if (!GetAce(
      lpDacl,    // адрес DACL
      i,         // индекс элемента
      &lpAce))   // указатель на элемент списка
    {
      dwRetCode = GetLastError();
      printf("Get ace failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
    // проверяем тип элемента
    if (((ACE_HEADER*)lpAce)->AceType == ACCESS_DENIED_ACE_TYPE)
      // удаляем элемент из списка DACL
      if (!DeleteAce( lpDacl,  i))
      {
        dwRetCode = GetLastError();
        printf("Delete ace failed.\n");
        printf("Error code: %d\n", dwRetCode);
        
        return dwRetCode;
      }
  }
  // устанавливаем новый дескриптор безопасности
  if (!SetFileSecurity(
    chDirName,                   // имя файла
    DACL_SECURITY_INFORMATION,   // устанавливаем DACL
    lpSd))                       // адрес дескриптора безопасности
  {
    dwRetCode = GetLastError();
    printf("Set file security failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  printf("Denied elements are deleted from the DACL.\n");
  
  // освобождаем память
  delete[] lpSd;
  
  return 0;
}