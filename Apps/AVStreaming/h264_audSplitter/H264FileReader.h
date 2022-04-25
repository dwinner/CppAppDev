#ifndef H264_NALPARSERSAMPLE_H264FILEREADER_H
#define H264_NALPARSERSAMPLE_H264FILEREADER_H

#include "Nalu.h"
#include <memory>
#include <regex>
#include <string>
#include <vector>

class H264FileReader
{
public:
    explicit H264FileReader(const std::string& h264FileName);

    std::unique_ptr<std::valarray<std::unique_ptr<Nalu>>> GetNalUnits() const;

    H264FileReader(const H264FileReader& other) = default;

    H264FileReader(H264FileReader&& other) noexcept
        : h264FileName_ { std::move(other.h264FileName_) }
    {
    }

    H264FileReader& operator=(H264FileReader other)
    {
        using std::swap;
        swap(*this, other);
        return *this;
    }

    ~H264FileReader();

private:
    std::string h264FileName_;

    inline static const std::string AudNaluPattern = R"((\0\0\0?\x01[\x09\x29\x49\x69].))";

    inline static const std::regex AudNaluRegEx { AudNaluPattern };

    static std::vector<std::string> SplitByRegex(const std::string& inputString);
};

#endif // H264_NALPARSERSAMPLE_H264FILEREADER_H
