#include <iostream>
#include <functional>
#include <atlstr.h>
#include <thread>
#include <tlhelp32.h>
#include "LineBuffer.h"
/*
C:\a\local\path> pushd \\network_host\a\network\path
U:\a\network\path> REM a temporary U: virtual drive has been created
U:\a\network\path> popd
C:\a\local\path> REM the U: drive has been deleted
C:\a\local\path>
*/
int Exec(const CString& command, const CString& arguments, const std::function<void(const char*)>& outputProc);

CString GetLastErrorAsString();

using namespace std;

int main()
{
    try
    {
        string command="pushd";
        string args={R"(\\A929\d$\caneasy\Debug)"};
        string log="";
        Exec(command.c_str(), args.c_str(), [&log](const char* out)
        {
            log.append(out);
        });
    }
    catch (const std::runtime_error& error)
    {
        cout<<error.what();
    }

    return 0;
}

int Exec(const CString& command, const CString& arguments, const std::function<void(const char*)>& outputProc)
{
    auto defaultStartUpDir = "c:\\Windows\\System32";
    constexpr size_t bufSize = 4096;

    HANDLE childStdReadHandle = nullptr;
    HANDLE childStdWriteHandle = nullptr;
    PROCESS_INFORMATION processInf = {};
    SECURITY_ATTRIBUTES securityAttrs;
    securityAttrs.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttrs.bInheritHandle = TRUE;
    securityAttrs.lpSecurityDescriptor = nullptr;

    if (!CreatePipe(&childStdReadHandle, &childStdWriteHandle, &securityAttrs, 0))
    {
        throw std::runtime_error("Can't start process (pipe hasn't been created)");
    }

    if (!SetHandleInformation(childStdReadHandle,HANDLE_FLAG_INHERIT, 0))
    {
        throw std::runtime_error("Can't start process (SetHandleInformation failed)");
    }

    std::thread readThread([=]()
    {
        DWORD dwRead;
        CHAR chBuf[bufSize];
        LineBuffer lineBuffer;
        for (;;)
        {
            ZeroMemory(chBuf, bufSize);
            auto bSuccess = ReadFile(childStdReadHandle, chBuf, bufSize, &dwRead, nullptr);
            if (!bSuccess || dwRead == 0)
            {
                break;
            }

            auto lines = lineBuffer.append(chBuf);
            if (outputProc)
            {
                for (auto& line : lines)
                {
                    outputProc((line + '\n').c_str());
                }
            }
        }
    });

    STARTUPINFO startUpInf = {};
    startUpInf.cb = sizeof(STARTUPINFO);
    startUpInf.hStdError = childStdWriteHandle;
    startUpInf.hStdOutput = childStdWriteHandle;
    startUpInf.dwFlags = STARTF_USESTDHANDLES;

    CString commandLine = command + " " + arguments;
    LPCSTR cmdStr = commandLine.GetString();
    auto cmdLine = LPSTR(cmdStr);
    LPCSTR appName = nullptr;
    LPSECURITY_ATTRIBUTES procAttrs = nullptr;
    LPSECURITY_ATTRIBUTES thrAttrs = nullptr;
    BOOL inheritHdls = TRUE;
    DWORD creationFlags = CREATE_NO_WINDOW;
    LPVOID lpEnv = nullptr;
    LPCSTR currentDir = defaultStartUpDir; // force the current directory to window's default

    BOOL createResult = CreateProcess(
        appName, cmdLine, procAttrs, thrAttrs, inheritHdls, creationFlags, lpEnv, currentDir, &startUpInf, &processInf);
    if (!createResult)
    {
        CloseHandle(childStdReadHandle);
        CString errorMessage;
        auto lastError = GetLastErrorAsString().GetString();
        errorMessage.Format("Can't create process (Error:%s)", lastError);
        throw std::runtime_error(errorMessage);
    }

    CloseHandle(childStdWriteHandle);
    WaitForSingleObject(processInf.hProcess, INFINITE);
    DWORD exitCode;
    GetExitCodeProcess(processInf.hProcess, &exitCode);
    readThread.join();
    CloseHandle(processInf.hThread);
    CloseHandle(processInf.hProcess);
    CloseHandle(childStdReadHandle);

    return static_cast<int>(exitCode);
}

CString GetLastErrorAsString()
{
    //Get the error message ID, if any.
    DWORD errorMessageID = GetLastError();
    if (errorMessageID == 0)
    {
        return ""; //No error message has been recorded
    }

    LPSTR messageBuffer = nullptr;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        errorMessageID,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&messageBuffer, 0, nullptr);

    CString message(messageBuffer, size);

    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
    return message;
}
