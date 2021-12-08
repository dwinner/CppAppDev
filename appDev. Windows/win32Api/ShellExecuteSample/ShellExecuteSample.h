#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

inline std::string getUserHomeDir();

inline bool installExtension(const std::string& vsCodeCmd, const std::string& extensionPath, bool install = true);

std::vector<fs::path> findFiles(const fs::path& dir, std::function<bool(const fs::path&)> filter);

fs::path findVsix(const std::string& similarName = "caneasy");

std::string normalizeVsix(const fs::path& vsixPath, const std::string& vendorName = "schleisheimer");
