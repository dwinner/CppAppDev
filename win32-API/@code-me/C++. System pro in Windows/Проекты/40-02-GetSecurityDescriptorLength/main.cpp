#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hProcess;        // дескриптор процесса
  HANDLE  hTokenHandle;    // дескриптор маркера доступа

  TOKEN_OWNER  *lpOwnerSid = NULL;   // указатель на буфер
  DWORD  dwOwnerLength= 0;           // длина буфера

  TOKEN_OWNER  *lpPrimaryGroupSid = NULL;  // указатель на буфер
  DWORD  dwPrimaryGroupLength= 0;          // длина буфера

  SECURITY_DESCRIPTOR  sd;     // SD в абсолютной форме
  SECURITY_DESCRIPTOR  *lpSd;  // указатель на SD в относительной форме
  
  DWORD dwErrCode;       // код возврата
  DWORD dwLength;        // длина дескриптора безопасности

  // получить дескриптор процесса
  hProcess = GetCurrentProcess();
  // получить маркер доступа процесса
  if (!OpenProcessToken(
    hProcess,        // дескриптор процесса
    TOKEN_QUERY,     // запрос информации из маркера
    &hTokenHandle))  // дескриптор маркера
  {
    dwErrCode = GetLastError();
    cout << "Open process token failed: " << dwErrCode << endl;

    return dwErrCode;
  }
  // определяем длину SID владельца
  if (!GetTokenInformation(
    hTokenHandle,      // дескриптор маркера доступа  
    TokenOwner,        // получаем SID владельца
    NULL,              // нужна длина буфера
    0,                 // пока длина равна 0
    &dwOwnerLength))   // для длины буфера
  {
    if (dwOwnerLength != 0)
      // захватываем память под SID
      lpOwnerSid = (TOKEN_OWNER*)new char[dwOwnerLength];
    else
    {
      // выходим из программы
      dwErrCode = GetLastError();
      cout << "Get token information for length failed: " 
           << dwErrCode << endl;

      return dwErrCode;
    }
  }

  // определяем SID владельца
  if (!GetTokenInformation(
    hTokenHandle,      // дескриптор маркера доступа
    TokenOwner,        // нужен SID маркера доступа
    lpOwnerSid,        // адрес буфера для SID
    dwOwnerLength,     // длина буфера
    &dwOwnerLength))   // длина буфера
  {
    dwErrCode = GetLastError();
    cout << "Get token information failed: " << dwErrCode << endl;

    return dwErrCode;
  }

  // определяем длину SID первичной группы владельца
  if (!GetTokenInformation(
    hTokenHandle,            // дескриптор маркера доступа  
    TokenPrimaryGroup,       // получаем SID первичной группы
    NULL,                    // нужна длина буфера
    0,                       // пока длина равна 0
    &dwPrimaryGroupLength))  // для длины буфера
  {
    if (dwPrimaryGroupLength != 0)
      // захватываем память под SID
      lpPrimaryGroupSid = (TOKEN_OWNER*)new char[dwPrimaryGroupLength];
    else
    {
      // выходим из программы
      dwErrCode = GetLastError();
      cout << "Get token information for length failed: " 
           << dwErrCode << endl;

      return dwErrCode;
    }
  }

  // определяем SID первичной группы владельца
  if (!GetTokenInformation(
    hTokenHandle,            // дескриптор маркера доступа
    TokenPrimaryGroup,       // нужен SID первичной группыа
    lpPrimaryGroupSid,       // адрес буфера для SID
    dwPrimaryGroupLength,    // длина буфера
    &dwPrimaryGroupLength))  // длина буфера
  {
    dwErrCode = GetLastError();
    cout << "Get token information failed: " << dwErrCode << endl;

    return dwErrCode;
  }
  
  // инициализируем дескриптор безопасности
  if (!InitializeSecurityDescriptor(     // инициализируем версию
    &sd,
    SECURITY_DESCRIPTOR_REVISION))
  {
    dwErrCode = GetLastError();
    cerr << "Initialize security descriptor failed." << endl
      << "The last error code: " << dwErrCode << endl;
    cout << "Press any key to finish." << endl;
    cin.get();

    return dwErrCode;
  }

  // устанавливаем SID владельца объекта
  if (!SetSecurityDescriptorOwner(
    &sd,
    lpOwnerSid->Owner,
    FALSE))
  {
    dwErrCode = GetLastError();
    cerr << "Set security descriptor owner failed." << endl
      << "The last error code: " << dwErrCode << endl;
    cout << "Press any key to finish." << endl;
    cin.get();

    return dwErrCode;
  }

  // устанавливаем SID первичной группы владельца
  if (!SetSecurityDescriptorGroup(
    &sd,
    lpPrimaryGroupSid->Owner,
    FALSE))
  {
    dwErrCode = GetLastError();
    cerr << "Set security descriptor group failed." << endl
      << "The last error code: " << dwErrCode << endl;
    cout << "Press any key to finish." << endl;
    cin.get();

    return dwErrCode;
  }

  // проверяем структуру дескриптора безопасности
  if (!IsValidSecurityDescriptor(&sd))
  {
    dwErrCode = GetLastError();
    cerr << "The security descriptor is invalid." << endl
      << "The last error code: " << dwErrCode << endl;
    cout << "Press any key to finish." << endl;
    cin.get();

    return dwErrCode;
  }

  // печатаем длину структуры SECURITY_DESCRIPTOR
  cout << "Length of SECURITY_DESCRIPTOR structure: " 
       << sizeof(sd) << endl;

  // получаем и печатаем длину дескриптора безопасности 
  // в абсолютной форме
  dwLength = GetSecurityDescriptorLength(&sd);
  cout << "Length of security descriptor in absolute form: " 
       << dwLength << endl;

  // создаем дескриптор безопаснотсти в относительной форме
  lpSd = (SECURITY_DESCRIPTOR*)new char[dwLength];
  if (!MakeSelfRelativeSD(&sd, lpSd, &dwLength))
  {
    dwErrCode = GetLastError();
    cerr << "Make self relative SD failed." << endl
      << "The last error code: " << dwErrCode << endl;
    cout << "Press any key to finish." << endl;
    cin.get();

    return dwErrCode;
  }

  cout << "The self realtive security descriptor is made." << endl;

  // освобождаем память
  delete[] lpOwnerSid;
  delete[] lpPrimaryGroupSid;
  delete[] lpSd;

  // закрываем дескрипторы
  CloseHandle(hTokenHandle);

  return 0;
}