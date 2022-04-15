#include "H264FileReader.h"
#include <vector>
#include <fstream>
#include <regex>

H264FileReader::~H264FileReader() = default;

H264FileReader::H264FileReader(const std::string &h264FileName)
{
    h264FileName_ = h264FileName;
}

std::unique_ptr<std::valarray<std::unique_ptr<Nalu>>> H264FileReader::GetNalUnits() const
{
    using namespace std;

    ifstream h264FileStream(h264FileName_, ios::binary);
    string h264Content((std::istreambuf_iterator<char>(h264FileStream)),
                       (std::istreambuf_iterator<char>()));
    vector<string> splitByAudList = SplitByRegex(h264Content, audNaluPattern);
    size_t nalUnitsCount = splitByAudList.size();
    auto naluValues = make_unique<valarray<unique_ptr<Nalu>>>(nalUnitsCount);

    // iterate through the NAL-units
    for (size_t naluIdx = 0; naluIdx < nalUnitsCount; naluIdx++)
    {
        string strContent = splitByAudList[naluIdx];
        const size_t length = strContent.length();
        valarray<uint8_t> content = valarray<uint8_t>(length);
        for (size_t strIdx = 0; strIdx < length; strIdx++)
        {
            content[strIdx] = static_cast<uint8_t>(strContent[strIdx]);
        }

        (*naluValues)[naluIdx] = make_unique<Nalu>(length, content);
    }

    return naluValues;
}

std::vector<std::string> H264FileReader::SplitByRegex(const std::string &inputString, const std::string &regEx)
{
    using namespace std;

    static regex reInstance{regEx};
    sregex_token_iterator start{inputString.begin(), inputString.end(), reInstance, -1}, end;

    return vector<string>(start, end);
}
