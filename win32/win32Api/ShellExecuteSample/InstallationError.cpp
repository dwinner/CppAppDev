#include "pch.h"
#include "InstallationError.h"

vscode::InstallationError::InstallationError(std::string message)
   : message_(std::move(message))
{
}

const char* vscode::InstallationError::what() const
{
   return message_.c_str();
}
