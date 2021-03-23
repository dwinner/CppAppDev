#include <windows.h>
#include <iostream.h>

int main()
{
  HANDLE  hProcess;        // ���������� ��������
  HANDLE  hTokenHandle;    // ���������� ������� �������

  TOKEN_OWNER  *lpOwnerSid = NULL;   // ��������� �� �����
  DWORD  dwOwnerLength= 0;           // ����� ������

  TOKEN_OWNER  *lpPrimaryGroupSid = NULL;  // ��������� �� �����
  DWORD  dwPrimaryGroupLength= 0;          // ����� ������

  SECURITY_DESCRIPTOR  sd;     // SD � ���������� �����
  SECURITY_DESCRIPTOR  *lpSd;  // ��������� �� SD � ������������� �����
  
  DWORD dwErrCode;       // ��� ��������
  DWORD dwLength;        // ����� ����������� ������������

  // �������� ���������� ��������
  hProcess = GetCurrentProcess();
  // �������� ������ ������� ��������
  if (!OpenProcessToken(
    hProcess,        // ���������� ��������
    TOKEN_QUERY,     // ������ ���������� �� �������
    &hTokenHandle))  // ���������� �������
  {
    dwErrCode = GetLastError();
    cout << "Open process token failed: " << dwErrCode << endl;

    return dwErrCode;
  }
  // ���������� ����� SID ���������
  if (!GetTokenInformation(
    hTokenHandle,      // ���������� ������� �������  
    TokenOwner,        // �������� SID ���������
    NULL,              // ����� ����� ������
    0,                 // ���� ����� ����� 0
    &dwOwnerLength))   // ��� ����� ������
  {
    if (dwOwnerLength != 0)
      // ����������� ������ ��� SID
      lpOwnerSid = (TOKEN_OWNER*)new char[dwOwnerLength];
    else
    {
      // ������� �� ���������
      dwErrCode = GetLastError();
      cout << "Get token information for length failed: " 
           << dwErrCode << endl;

      return dwErrCode;
    }
  }

  // ���������� SID ���������
  if (!GetTokenInformation(
    hTokenHandle,      // ���������� ������� �������
    TokenOwner,        // ����� SID ������� �������
    lpOwnerSid,        // ����� ������ ��� SID
    dwOwnerLength,     // ����� ������
    &dwOwnerLength))   // ����� ������
  {
    dwErrCode = GetLastError();
    cout << "Get token information failed: " << dwErrCode << endl;

    return dwErrCode;
  }

  // ���������� ����� SID ��������� ������ ���������
  if (!GetTokenInformation(
    hTokenHandle,            // ���������� ������� �������  
    TokenPrimaryGroup,       // �������� SID ��������� ������
    NULL,                    // ����� ����� ������
    0,                       // ���� ����� ����� 0
    &dwPrimaryGroupLength))  // ��� ����� ������
  {
    if (dwPrimaryGroupLength != 0)
      // ����������� ������ ��� SID
      lpPrimaryGroupSid = (TOKEN_OWNER*)new char[dwPrimaryGroupLength];
    else
    {
      // ������� �� ���������
      dwErrCode = GetLastError();
      cout << "Get token information for length failed: " 
           << dwErrCode << endl;

      return dwErrCode;
    }
  }

  // ���������� SID ��������� ������ ���������
  if (!GetTokenInformation(
    hTokenHandle,            // ���������� ������� �������
    TokenPrimaryGroup,       // ����� SID ��������� �������
    lpPrimaryGroupSid,       // ����� ������ ��� SID
    dwPrimaryGroupLength,    // ����� ������
    &dwPrimaryGroupLength))  // ����� ������
  {
    dwErrCode = GetLastError();
    cout << "Get token information failed: " << dwErrCode << endl;

    return dwErrCode;
  }
  
  // �������������� ���������� ������������
  if (!InitializeSecurityDescriptor(     // �������������� ������
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

  // ������������� SID ��������� �������
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

  // ������������� SID ��������� ������ ���������
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

  // ��������� ��������� ����������� ������������
  if (!IsValidSecurityDescriptor(&sd))
  {
    dwErrCode = GetLastError();
    cerr << "The security descriptor is invalid." << endl
      << "The last error code: " << dwErrCode << endl;
    cout << "Press any key to finish." << endl;
    cin.get();

    return dwErrCode;
  }

  // �������� ����� ��������� SECURITY_DESCRIPTOR
  cout << "Length of SECURITY_DESCRIPTOR structure: " 
       << sizeof(sd) << endl;

  // �������� � �������� ����� ����������� ������������ 
  // � ���������� �����
  dwLength = GetSecurityDescriptorLength(&sd);
  cout << "Length of security descriptor in absolute form: " 
       << dwLength << endl;

  // ������� ���������� ������������� � ������������� �����
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

  // ����������� ������
  delete[] lpOwnerSid;
  delete[] lpPrimaryGroupSid;
  delete[] lpSd;

  // ��������� �����������
  CloseHandle(hTokenHandle);

  return 0;
}