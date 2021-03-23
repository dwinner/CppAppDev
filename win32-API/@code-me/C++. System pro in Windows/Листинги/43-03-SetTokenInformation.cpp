#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>
#include <lm.h>
#include <sddl.h>

int main()
{
  HANDLE hMutex;         // дескриптор мьютекса
  HANDLE hProcess;       // дескриптор процесса
  HANDLE hTokenHandle;   // дескриптор маркера доступа
  
  ACL *lpDacl;           // указатель на список доступа
  void *lpAce = NULL;    // указатель на элемент списка
  
  BOOL bDaclPresent;     // признак присутствия списка DACL
  BOOL bDaclDefaulted;   // признак списка DACL по умолчанию
  
  char chUserName[UNLEN];  // имя пользователя
  
  DWORD dwLengthOfDomainName = 0;  // длина имени домена
  DWORD dwLengthOfSid = 0;   // длина разрешающего SID
  
  DWORD dwDaclLength = 0;    // длина списка доступа
  DWORD dwRetLength = 0;     // возвращаемая длина буфера
  
  SID *lpSid = NULL;         // указатель на разрешающий SID
  LPTSTR lpDomainName = NULL;    // указатель на имя домена
  SID_NAME_USE typeOfSid;    // тип учетной записи
  
  PSECURITY_DESCRIPTOR lpSd = NULL;  // указатель на SD
  DWORD dwLengthOfSd = 0;    // длина дескриптора безопасности
  
  LPTSTR StringSid;    // указатель на строку SID
  
  DWORD dwRetCode;     // код возврата
  
  // получаем дескриптор процесса
  hProcess = GetCurrentProcess();
  
  // открываем маркер доступа процесса
  if (!OpenProcessToken(
    hProcess,        // дескриптор процесса
    TOKEN_QUERY |    // получаем информацию из маркера доступа 
    TOKEN_ADJUST_DEFAULT,  // и измененяем список DACL маркера доступа
    &hTokenHandle))  // дескриптор маркера
  {
    dwRetCode = GetLastError();
    printf( "Open process token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // вводим имя пользователя, которому разрешим доступ к каталогу
  printf("Input a user name: ");
  gets(chUserName);
  
  // определяем длину SID пользователя
  if (!LookupAccountName(
    NULL,            // ищем имя на локальном компьютере
    chUserName,      // имя пользователя
    NULL,            // определяем длину SID
    &dwLengthOfSid,  // длина SID
    NULL,            // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &typeOfSid))     // тип учетной записи
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // распределяем память для SID и имени домена
      lpSid = (SID*) new char[dwLengthOfSid];
      lpDomainName = (LPTSTR) new char[dwLengthOfDomainName];
    }
    else
    {
      // выходим из программы
      printf("Lookup account name failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
  }
  
  // определяем SID и имя домена пользователя
  if(!LookupAccountName(
    NULL,            // ищем имя на локальном компьютере
    chUserName,      // имя пользователя
    lpSid,           // указатель на SID
    &dwLengthOfSid,  // длина SID
    lpDomainName,    // указатель на имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &typeOfSid))     // тип учетной записи
  {
    dwRetCode = GetLastError();
    
    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // преобразуем SID в строку
  if (!ConvertSidToStringSid(
    lpSid,
    &StringSid))
  {
    dwRetCode = GetLastError();
    printf("Convert sid to string sid failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  // печатем SID
  printf("%s\n",StringSid);
  LocalFree(StringSid);
  
  // определем длину списка DACL
  dwDaclLength = sizeof(ACL)
    + sizeof(ACCESS_ALLOWED_ACE) 
    - sizeof(DWORD) + dwLengthOfSid;
  
  // распределяем память под DACL
  lpDacl = (ACL*)new char[dwDaclLength];
  
  // инициализируем список DACL
  if (!InitializeAcl(
    lpDacl,          // адрес DACL
    dwDaclLength,    // длина DACL
    ACL_REVISION))   // версия DACL
  {
    dwRetCode = GetLastError();
    
    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // добавляем разрешающий элемент в список DACL
  if (!AddAccessAllowedAce(
    lpDacl,        // адрес DACL
    ACL_REVISION,  // версия DACL
    GENERIC_ALL,   // разрешаем все родовые права доступа
    lpSid))        // адрес SID
  {
    dwRetCode = GetLastError();
    perror("Add access allowed ace failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  
  // устанавливает новый DACL по умолчанию в маркер доступа
  if (!SetTokenInformation(
    hTokenHandle,      // дескриптор маркера доступа
    TokenDefaultDacl,  // устанавливаем список DACL
    &lpDacl,           // адрес буфера с новым списком DACL
    dwDaclLength))     // размер буфера
  {
    dwRetCode = GetLastError();
    printf( "Set token information failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // создаем мьютекс
  hMutex = CreateMutex(NULL, FALSE, "DemoMutex");
  if (hMutex == NULL)
  {
    dwRetCode = GetLastError();
    perror("Create mutex failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
    return dwRetCode;
  }
  printf("The mutex is created.\n");
  
  // освобождаем память
  delete[] lpSid;
  delete[] lpDomainName;
  delete[] lpDacl;
  
  // теперь проверяем список DACL мьютекса
  
  // определяем требуемую длину буфера
  if (!GetKernelObjectSecurity(
    hMutex,          // дескриптор мьютекса
    DACL_SECURITY_INFORMATION,   // получаем список DACL мьютекса
    lpSd,            // адрес SD
    0,               // определяем длину буфера
    &dwLengthOfSd))  // требуемая длина буфера
  {
    dwRetCode = GetLastError();
    
    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
      // распределяем память для буфера
      lpSd = (SECURITY_DESCRIPTOR*) new char[dwLengthOfSd];
    else
    {
      // выходим из программы
      printf("Get kernel object security failed.\n");
      printf("Error code: %d\n", dwRetCode);
      
      return dwRetCode;
    }
  }
  
  // чтаем идентификатор безопасности мьютекса
  if (!GetKernelObjectSecurity(
    hMutex,          // дескриптор мьютекса
    DACL_SECURITY_INFORMATION,   // получаем список DACL мьютекса
    lpSd,            // адрес SD
    dwLengthOfSd,    // длина буфера
    &dwLengthOfSd))  // требуемая длина буфера
  {
    dwRetCode = GetLastError();
    printf("Get kernel object security failed.\n");
    printf("The last error code: %u\n", dwRetCode);
    
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
    printf("Dacl is not present.\n");
    return 0;
  }
  else
    printf("Dacl is present.\n");

  // проверяем, установлен ли DACL пользователем
  if (bDaclDefaulted == SE_DACL_DEFAULTED)
    printf("Dacl is defaulted.\n");
  else
    printf("Dacl is not defaulted.\n");

  
  // печатаем количество элементов
  printf("Ace count: %u\n", lpDacl->AceCount);
  
  // получаем элементы списка DACL
  for (unsigned i = 0; i < lpDacl->AceCount; ++i)
  {
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
      // печатаем SID
      printf("%s\n",StringSid);
      LocalFree(StringSid);
    }
  }
  
  // освобождаем память
  delete[] lpSd;
  
  CloseHandle(hMutex);
  CloseHandle(hTokenHandle);
  
  return 0;
}