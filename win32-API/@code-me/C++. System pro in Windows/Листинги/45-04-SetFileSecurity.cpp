#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <lm.h>

int main()
{
  wchar_t wchDirName[248];       // имя каталога
  wchar_t wchUserName[UNLEN];    // имя пользователя
  
  ACL *lpOldDacl;    // указатель на старый DACL
  ACL *lpNewDacl;    // указатель на новый DACL
  LPVOID lpAce;      // указатель на элемент ACE
  
  DWORD dwDaclLength = 0;        // длина DACL
  DWORD dwSdLength = 0;          // длина SD
  DWORD dwSidLength = 0;         // длина SID
  DWORD dwLengthOfDomainName = 0;    // длина имени домена
  
  PSID lpSid = NULL;             // указатель на разрешающий SID
  LPTSTR lpDomainName = NULL;    // указатель на имя домена
  
  SID_NAME_USE typeOfSid;        // тип учетной записи
  
  SECURITY_DESCRIPTOR *lpSd = NULL;  // адрес дескриптора безопасности
  SECURITY_DESCRIPTOR sdAbsoluteSd;  // абсолютный формат SD
  BOOL bDaclPresent;             // признак присутствия списка DACL
  BOOL bDaclDefaulted;           // признак списка DACL по умолчанию
  
  DWORD dwRetCode;   // код возврата

  // читаем имя файла или каталога
  printf("Input a file or directory name: ");
  _getws(wchDirName);
  
  // получаем длину дескриптора безопасности
  if (!GetFileSecurity(
    wchDirName,    // имя файла
    DACL_SECURITY_INFORMATION,   // получаем DACL
    lpSd,          // адрес дескриптора безопасности
    0,             // определяем длину буфера
    &dwSdLength))  // адрес для требуемой длины
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
      // распределяем память для буфера
      lpSd = (SECURITY_DESCRIPTOR*) new char[dwSdLength];
    else
    {
      // выходим из программы
      printf("Get file security failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
  }

  // читаем дескриптор безопасности
  if (!GetFileSecurity(
    wchDirName,    // имя файла
    DACL_SECURITY_INFORMATION,   // получаем DACL
    lpSd,          // адрес дескриптора безопасности
    dwSdLength,    // длину буфера
    &dwSdLength))  // адрес для требуемой длины
  {
    dwRetCode = GetLastError();
    printf("Get file security failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // вводим имя пользователя, которого добавляем в DACL
  printf("Input a user name: ");
  _getws(wchUserName);
  
  // определяем длину SID пользователя
  if (!LookupAccountName(
    NULL,          // ищем имя на локальном компьютере
    wchUserName,   // имя пользователя
    NULL,          // определяем длину SID
    &dwSidLength,  // длина SID
    NULL,          // определяем имя домена
    &dwLengthOfDomainName,     // длина имени домена
    &typeOfSid))   // тип учетной записи
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // распределяем память для SID
      lpSid = (SID*) new char[dwSidLength];
      lpDomainName = (LPTSTR) new wchar_t[dwLengthOfDomainName];
    }
    else
    {
      // выходим из программы
      printf("Lookup account name failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
  }
  
  // определяем SID
  if(!LookupAccountName(
    NULL,          // ищем имя на локальном компьютере
    wchUserName,   // имя пользователя
    lpSid,         // указатель на SID
    &dwSidLength,  // длина SID
    lpDomainName,  // указатель на имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &typeOfSid))   // тип учетной записи
  {
    dwRetCode = GetLastError();
    
    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // получаем список DACL из дескриптора безопасности
  if (!GetSecurityDescriptorDacl(
    lpSd,              // адрес дескриптора безопасности
    &bDaclPresent,     // признак присутствия списка DACL
    &lpOldDacl,        // адрес указателя на DACL
    &bDaclDefaulted))  // признак списка DACL по умолчанию
  {
    dwRetCode = GetLastError();
    printf("Get security descriptor DACL failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // определяем длину нового DACL
  dwDaclLength = lpOldDacl->AclSize + 
    sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) + dwSidLength;

  // распределяем память под новый DACL
  lpNewDacl = (ACL*)new char[dwDaclLength];

  // инициализируем новый DACL
  if (!InitializeAcl(
    lpNewDacl,       // адрес DACL
    dwDaclLength,    // длина DACL
    ACL_REVISION))   // версия DACL
  {
    dwRetCode = GetLastError();
    
    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // добавляем нового элемент в новый DACL
  if (!AddAccessDeniedAce(
    lpNewDacl,       // адрес DACL
    ACL_REVISION,    // версия DACL
    FILE_WRITE_ATTRIBUTES,  // запрещаем писать атрибуты
    lpSid))          // адрес SID
  {
    dwRetCode = GetLastError();
    perror("Add access allowed ace failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // получаем адрес первого ACE в старом списке DACL
  if (!GetAce(
    lpOldDacl,     // адрес старого DACL
    0,             // ищем первый элемент
    &lpAce))       // адрес первого элемента
  {
    dwRetCode = GetLastError();
    
    printf("Get ace failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }

  // переписываем элементы из старого DACL в новый DACL
  if (bDaclPresent)
  {
    if (!AddAce(
      lpNewDacl,       // адрес нового DACL
      ACL_REVISION,    // версия DACL
      MAXDWORD,        // добавляем в конец списка
      lpAce,           // адрес старого DACL
      lpOldDacl->AclSize - sizeof(ACL)))  // длина старого DACL
    {
      dwRetCode = GetLastError();
      perror("Add access allowed ace failed.\n");
      printf("The last error code: %u\n", dwRetCode);
      
      return dwRetCode;
    }
  }

  // проверяем достоверность DACL
  if (!IsValidAcl(lpNewDacl))
  {
    dwRetCode = GetLastError();
    perror("The new ACL is invalid.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // создаем новый дескриптор безопасности в абсолютной форме
  if (!InitializeSecurityDescriptor(
    &sdAbsoluteSd,       // адрес структуры SD
    SECURITY_DESCRIPTOR_REVISION))
  {
    dwRetCode = GetLastError();
    perror("Initialize security descriptor failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // устанавливаем DACL  в новый дескриптор безопасности
  if (!SetSecurityDescriptorDacl(
    &sdAbsoluteSd,   // адрес дескриптора безопасности
    TRUE,            // DACL присутствует
    lpNewDacl,       // указатель на DACL
    FALSE))          // DACL не задан по умолчанию
  {
    dwRetCode = GetLastError();
    perror("Set security descriptor DACL failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // проверяем структуру дескриптора безопасности
  if (!IsValidSecurityDescriptor(&sdAbsoluteSd))
  {
    dwRetCode = GetLastError();
    perror("Security descriptor is invalid.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  // устанавливаем новый дескриптор безопасности
  if (!SetFileSecurity(
    wchDirName,        // имя файла
    DACL_SECURITY_INFORMATION,     // устанавливаем DACL
    &sdAbsoluteSd))    // адрес дескриптора безопасности
  {
    dwRetCode = GetLastError();
    printf("Set file security failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // освобождаем память
  delete[] lpSd;
  delete[] lpSid;
  delete[] lpDomainName;
  delete[] lpNewDacl;

  return 0;
}