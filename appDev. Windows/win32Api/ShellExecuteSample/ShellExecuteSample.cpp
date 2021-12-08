/**
 * Installing / managing VS-code extensions from C++
 */

#include "pch.h"
#include "framework.h"
#include <cassert>
#include <filesystem>
#include <string>
#include <regex>
#include "ExtensionInstaller.h"
#include "InstallationError.h"

using namespace std;
using namespace vscode;
namespace fs = std::filesystem;

int main()
{
   try
   {
      const string codeCmdPath = R"(c:\Users\vinevtsev\AppData\Local\Programs\Microsoft VS Code\bin\code.cmd)";
      assert(fs::exists(codeCmdPath));
      const HMODULE hModule = ::GetModuleHandle(nullptr);
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

      ExtensionInstaller installer("schleisheimer", "caneasy", codeCmdPath);
      installer.Apply();

      return EXIT_SUCCESS;
   }
   catch (const InstallationError& installError)
   {
      std::cout << installError.what();
      return EXIT_FAILURE;
   }
   catch (...)
   {
      return EXIT_FAILURE;
   }
}
