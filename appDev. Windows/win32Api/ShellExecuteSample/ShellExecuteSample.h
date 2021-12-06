#pragma once

#include <sstream>
#include "resource.h"
#include <string>
#include <UserEnv.h>
#include <vector>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

inline std::string getUserHomeDir();

inline bool installExtension(const std::string& vsCodeCmd, const std::string& extensionPath, bool install = true);

std::vector<fs::path> findFiles(fs::path const& dir, std::function<bool(fs::path const&)> filter);
