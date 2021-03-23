#include <windows.h>
#include <stdio.h>

int main()
{
  HKEY hKey;       // ключ реестра
  
  DWORD dwLengthOfSd = 0;            // длина SD
  SECURITY_DESCRIPTOR *lpSd = NULL;  // SD ключа реестра
  
  PSID lpOwner;    // указатель на SID владельца
  BOOL bOwnerDefaulted = FALSE;      // признак владельца по умолчанию
  
  DWORD  dwLengthOfUserName = 0;     // длина имени учетной записи 
  DWORD  dwLengthOfDomainName = 0;   // длина имени домена
  
  LPTSTR  lpUserName = NULL;         // указатель на имя домена
  LPTSTR  lpDomainName = NULL;       // указатель на имя домена
  
  SID_NAME_USE type_of_SID;          // тип учетной записи
  
  DWORD dwRetCode;     // код возврата
  
  // открываем ключ каталога
  dwRetCode = RegOpenKeyEx(
    HKEY_LOCAL_MACHINE,    // локальная машина
    NULL,                  // открыть ключ локальной машины
    0,                     // зарезервировано
    KEY_QUERY_VALUE,       // получаем данные из ключа
    &hKey);                // адрес дескриптора ключа
  if (dwRetCode != ERROR_SUCCESS)
  {
    dwRetCode = GetLastError();
    printf("RegOpenKeyEx failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // определяем длину идентификатор безопасности сервиса
  dwRetCode = RegGetKeySecurity(
    hKey,            // дескриптор сервиса
    OWNER_SECURITY_INFORMATION,  // получаем владельца ключа реестра
    lpSd,            // адрес SD
    &dwLengthOfSd);  // требуемая длина буфера
  if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    // захватываем память под дескриптор безопасности
    lpSd = (SECURITY_DESCRIPTOR*)new char[dwLengthOfSd];
  else
  {
    printf("RegGetKeySecurity failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // читаем идентификатор безопасности ключа реестра
  dwRetCode = RegGetKeySecurity(
    hKey,            // дескриптор сервиса
    OWNER_SECURITY_INFORMATION,  // получаем владельца ключа реестра
    lpSd,            // адрес SD
    &dwLengthOfSd);  // требуемая длина буфера
  if (dwRetCode != ERROR_SUCCESS)
  {
    printf("RegGetKeySecurity failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // получаем SID владельца мьютекса
  if (!GetSecurityDescriptorOwner(
    lpSd,          // адрес дескриптора безопасности
    &lpOwner,      // адрес указателя на SID владельца
    &bOwnerDefaulted))   // признак владельца по умолчанию
  {
    dwRetCode = GetLastError();
    printf("Get security descriptor owner failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // проверяем, есть ли владелец
  if (lpOwner == NULL)
  {
    printf("The owner is not present.\n");
    
    return 0;
  }
  
  if (bOwnerDefaulted)
    printf("The owner is defaulted.\n");
  // определяем длину имени домена
  if(!LookupAccountSid(
    NULL,              // ищем на локальном компьютере
    lpOwner,           // указатель на SID
    lpUserName,        // имя пользователя
    &dwLengthOfUserName,     // длина имени пользователя
    lpDomainName,      // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))     // тип учетной записи
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // распределяем память под имя пользователя и имя домена
      lpUserName = (LPTSTR) new char[dwLengthOfUserName];
      lpDomainName = (LPTSTR) new char[dwLengthOfDomainName];
    }
    else
    {
      printf("Lookup account SID for length failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
  }
  
  // определяем имя учетной записи по SID
  if(!LookupAccountSid(
    NULL,              // ищем на локальном компьютере
    lpOwner,           // указатель на SID пользователя
    lpUserName,        // имя пользователя
    &dwLengthOfUserName,     // длина имени пользователя
    lpDomainName,      // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &type_of_SID))     // тип учетной записи
  {
    dwRetCode = GetLastError();
    
    printf("Lookup account SID failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  printf("Key owner name: %s\n", lpUserName);
  printf("Key owner domain name: %s\n", lpDomainName);
    // освобождаем память
  delete[] lpUserName;
  delete[] lpDomainName;
  delete[] lpSd;
  
  RegCloseKey(hKey);

  return 0;
}