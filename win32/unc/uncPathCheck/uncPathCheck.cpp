#include <regex>
#include <string>
#include <filesystem>
#include <iostream>

using namespace std;
using namespace filesystem;

bool IsUncPath(const std::string& path);

int main()
{
    string uncPath{R"(\\A929\d$\caneasy\Debug)"};
    string vsixFName{"caneasy-8.3.2-4.6aa8f6ca-12ec-4673-9dd0-2b9151fc29da.vsix"};

    // Get temp directory
    auto tempDir{temp_directory_path()};

    // build unc-path for vsix
    path uncVsix{uncPath};
    uncVsix /= vsixFName;

    // build tmp-path for vsix
    path tempVsix{tempDir};
    tempVsix /= vsixFName;

    // copy vsix into available local temp
    error_code errorCode;
    bool copyOk = copy_file(uncVsix, tempVsix, copy_options::overwrite_existing, errorCode);
    if (!copyOk)
    {
        cout << errorCode.message() << endl;
    }

    return 0;
}

bool IsUncPath(const std::string& path)
{
    const regex uncRegEx{
        R"(^\\\\([\w]+)\\([\w]+)\$(\\[\w]+)*)"
    };

    smatch uncMatched;
    const bool matchFound = regex_match(path, uncMatched, uncRegEx);

    return matchFound;
}
