#pragma once

#include <string>
#include <vector>

class LineBuffer
{
public:
    std::vector<std::string> append(const char* msg)
    {
        buffer_ += msg;
        std::vector<std::string> result;
        std::string accum;
        while (true)
        {
            auto pos1 = buffer_.find('\n');
            if (pos1 != std::string::npos)
            {
                result.push_back(buffer_.substr(0, pos1));
                auto pos2 = (pos1 == buffer_.length()) ? 0 : (buffer_[pos1 + 1] == '\n' ? pos1 + 1 : 0);
                buffer_.erase(0, pos2 == pos1 + 1 ? pos2 + 1 : pos1 + 1);
                continue;
            }

            break;
        }

        return result;
    }

private:
    std::string buffer_;
};
