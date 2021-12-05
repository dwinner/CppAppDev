#pragma once

#include <sstream>

#include "resource.h"
#include <string>
#include <UserEnv.h>

inline std::string getUserHomeDir();

inline bool installExtension(const std::string& vsCodeCmd, const std::string& extensionPath, bool install = true);
