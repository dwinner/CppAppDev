#include "pch.h"
#include "framework.h"
#include "ShellExecuteSample.h"
#include <filesystem>

using namespace std;

int main()
{
   auto currentExeDir = std::filesystem::current_path();

   HMODULE hModule = ::GetModuleHandle(nullptr);
   if (hModule == nullptr)
   {
      wprintf(L"Fatal Error: GetModuleHandle failed\n");
      return EXIT_FAILURE;
   }

   // initialize MFC and print and error on failure
   if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
   {
      wprintf(L"Fatal Error: MFC initialization failed\n");
      return EXIT_FAILURE;
   }

   /*
    * --install-extension caneasy-1.0.0.vsix
    * --uninstall-extension kmasif.capl-vector
    * "c:\Users\vinevtsev\AppData\Local\Programs\Microsoft VS Code\bin\code.cmd" --install-extension "d:\CanEasy\Multidebugger\Debug\caneasy-1.0.0.vsix"
    */
   auto operation = L"open";
   auto commandFile = L"cmd";
   auto commandParams =
      L"/c \"c:\\Users\\vinevtsev\\AppData\\Local\\Programs\\Microsoft VS Code\\bin\\code.cmd\" --install-extension caneasy-1.0.0.vsix";
   auto currentDir = nullptr;
   HINSTANCE retVal = ShellExecute(nullptr,
                                   operation,
                                   commandFile,
                                   commandParams,
                                   currentDir,
                                   SW_HIDE);

   return EXIT_SUCCESS;
}
