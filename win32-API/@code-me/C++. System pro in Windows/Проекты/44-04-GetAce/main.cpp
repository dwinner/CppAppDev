#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>
#include <sddl.h>

int main()
{
  char chDirName[248];   // имя файла
  
  PSECURITY_DESCRIPTOR lpSd = NULL;  // указатель на SD
  
  PACL lpDacl = NULL;    // указатель на список управления доступом
  BOOL bDaclPresent;     // признак присутствия списка DACL
  BOOL bDaclDefaulted;   // признак списка DACL по умолчанию
  
  void *lpAce = NULL;    // указатель на элемент списка
  LPTSTR StringSid;      // указатель на строку SID
  
  DWORD dwLength;        // длина дескриптора безопасности
  DWORD dwRetCode;       // код возврата
  
  // вводим имя файла
  printf("Input a directory or file name: ");
  gets(chDirName);
  
  // получаем длину дескриптора безопасности
  if (!GetFileSecurity(
    chDirName,     // имя файла
    DACL_SECURITY_INFORMATION,   // получаем DACL
    lpSd,          // адрес дескриптора безопасности
    0,             // определяем длину буфера
    &dwLength))    // адрес для требуемой длины
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

  // печатаем количество элементов
  printf("Ace count: %u\n", lpDacl->AceCount);
  
  // получаем элементы списка DACL
  for (unsigned i = 0; i < lpDacl->AceCount; ++i)
  {
    if (!GetAce(
      lpDacl,  // адрес DACL
      i,       // индекс элемента
      &lpAce)) // указатель на элемент списка
    {
      dwRetCode = GetLastError();
      printf("Get ace failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
    // выводим на печать тип элемента и SID
    if (((ACE_HEADER*)lpAce)->AceType == ACCESS_ALLOWED_ACE_TYPE)
    {
      printf("ACCESS_ALLOWED_ACE_TYPE\n");
      // преобразуем SID в строку
      if (!ConvertSidToStringSid(
        &((ACCESS_ALLOWED_ACE*)lpAce)->SidStart,
        &StringSid))
      {
        dwRetCode = GetLastError();
        printf("Convert sid to string sid failed.\n");
        printf("Error code: %d\n", dwRetCode);
        
        return dwRetCode;
      }
      printf("%s\n", StringSid);
      LocalFree(StringSid);
    }
    if (((ACE_HEADER*)lpAce)->AceType == ACCESS_DENIED_ACE_TYPE)
    {
      printf("ACCESS_DENIED_ACE_TYPE\n");
      // преобразуем SID в строку
      if (!ConvertSidToStringSid(
        &((ACCESS_DENIED_ACE*)lpAce)->SidStart,
        &StringSid))
      {
        dwRetCode = GetLastError();
        printf("Convert sid to string sid failed.\n");
        printf("Error code: %d\n", dwRetCode);
        
        return dwRetCode;
      }
      
      printf("%s\n", StringSid);
      LocalFree(StringSid);
    }
  }
  
  // освобождаем память
  delete[] lpSd;
  
  return 0;
}