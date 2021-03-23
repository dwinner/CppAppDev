#include <windows.h>
#include <stdio.h>
#include <lm.h>

extern "C" BOOL WINAPI CheckTokenMembership(HANDLE, PSID, PBOOL);

DWORD WINAPI thread(LPVOID lpSid)
{
  HANDLE hImperson;  // дескриптор замещенного потока
  BOOL bIsMember;    // признак присутствия SID

  DWORD dwRetCode;   // код возврата

  // получаем маркер доступа потока
  if (!OpenThreadToken(
    GetCurrentThread(),
    TOKEN_QUERY,
    FALSE,
    &hImperson))
  {
    dwRetCode = GetLastError();

    printf("Open Thread Token failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // проверяем принадлежность маркера доступа
  if (!CheckTokenMembership(
    hImperson,
    lpSid,
    &bIsMember))
  {
    dwRetCode = GetLastError();

    printf("Check token membership failed.\n");
    printf("Error code: %d\n", dwRetCode);

    CloseHandle(hImperson);

    return dwRetCode;
  }

  if (bIsMember)
    printf("The group is enabled.\n");
  else
    printf("The group is disabled or not present.\n");

  CloseHandle(hImperson);

  return 0;
}

int main()
{
  HANDLE hThread;
  DWORD IDThread;

  HANDLE hToken;       // дескриптор маркера доступа
  HANDLE hDuplicate;   // дескриптор дубликата маркера доступа
  
  char chGroupName[GNLEN];     // имя пользователя

  DWORD dwLengthOfUserName = GNLEN;  // длина имени учетной записи 

  DWORD dwLengthOfSID = 0;     // длина SID
  DWORD dwLengthOfDomainName = 0;    // длина имени домена
  
  PSID lpSid = NULL;           // указатель на проверяемый SID
  LPTSTR lpDomainName = NULL;  // указатель на имя домена
  
  SID_NAME_USE typeOfSid;      // тип учетной записи

  DWORD dwRetCode;             // код возврата
  
  printf("Input a group name: ");
  gets(chGroupName);           // вводим имя пользователя

  // определяем длину SID пользователя
  if (!LookupAccountName(
    NULL,            // ищем имя на локальном компьютере
    chGroupName,     // имя группы
    NULL,            // определяем длину SID
    &dwLengthOfSID,  // длина SID
    NULL,            // определяем имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &typeOfSid))     // тип учетной записи
  {
    dwRetCode = GetLastError();

    if (dwRetCode == ERROR_INSUFFICIENT_BUFFER)
    {
      // распределяем память для SID и имени домена
      lpSid = (SID*) new char[dwLengthOfSID];
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
    chGroupName,     // имя пользователя
    lpSid,           // указатель на SID
    &dwLengthOfSID,  // длина SID
    lpDomainName,    // указатель на имя домена
    &dwLengthOfDomainName,   // длина имени домена
    &typeOfSid))     // тип учетной записи
  {
    dwRetCode = GetLastError();

    printf("Lookup account name failed.\n");
    printf("Error code: %d\n", dwRetCode);

    return dwRetCode;
  }

  // проверяем тип идентификатора безопасности
  if (typeOfSid != SidTypeAlias)
  {
    printf("This is not an alias.\n");
    return 0;
  }
  
  // получаем маркер доступа процесса
  if (!OpenProcessToken(
    GetCurrentProcess(),   // дескриптор процесса
    TOKEN_DUPLICATE,       // дублирование маркера доступа
    &hToken))              // дескриптор маркера
  {
    dwRetCode = GetLastError();
    printf( "Open process token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // дублируем маркер доступа
  if (!DuplicateToken(
    hToken,          // маркер доступа
    SecurityImpersonation,   // уровень замещения
    &hDuplicate))    // адрес дубликата маркера доступа
  {
    dwRetCode = GetLastError();
    printf( "Duplicate token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // запускаем поток
  hThread = CreateThread(
    NULL,            // защита по умолчанию
    0,               // размер стека по умолчанию
    thread,          // адрес программы потока
    (LPVOID) lpSid,  // адрес проверяемого SID
    CREATE_SUSPENDED,  // подвешенное состояние потока
    &IDThread);      // идентификатор потока
  if (hThread == NULL)
  {
    printf("Create thread failed.\n");
    return GetLastError();
  }

  // устанавливаем замещающий маркер доступа для потока
  if (!SetThreadToken(
    &hThread,      // адрес дескриптора потока
    hDuplicate))   // дубликат маркера доступа
  {
    dwRetCode = GetLastError();
    printf( "Set thread token failed: %u\n", dwRetCode);
    
    return dwRetCode;
  }

  // возобновляем поток
  ResumeThread(hThread);

  // ждем завершение потока
  WaitForSingleObject(hThread, INFINITE);

  CloseHandle(hToken);
  CloseHandle(hThread);

  return 0;
}