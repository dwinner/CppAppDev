#include "H264FileReader.h"
#include <vector>
#include <fstream>
#include <regex>
#include <cassert>

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

   // Check parity before gathering frames
   assert(((nalUnitsCount - 1) % 2) == 0);

   auto naluValues = make_unique<valarray<unique_ptr<Nalu>>>((nalUnitsCount - 1) / 2);

   // iterate through the NAL-units, skip the 1st one - it's always empty
   size_t chunkIndex = 0;
   for (size_t naluIdx = 1; naluIdx < nalUnitsCount; naluIdx += 2)
   {
      string firstChunk = splitByAudList[naluIdx];
      const size_t firstChunkLen = firstChunk.length();

      string secondChunk = splitByAudList[naluIdx + 1];
      const size_t secondChunkLen = secondChunk.length();

      const size_t totalFrameLen = firstChunkLen + secondChunkLen;

      valarray<uint8_t> content = valarray<uint8_t>(totalFrameLen);
      size_t strIdx;
      for (strIdx = 0; strIdx < firstChunkLen; strIdx++)
      {
         content[strIdx] = static_cast<uint8_t>(firstChunk[strIdx]);
      }

      for (strIdx = 0; strIdx < secondChunkLen; strIdx++)
      {
         content[strIdx + firstChunkLen] = static_cast<uint8_t>(secondChunk[strIdx]);
      }

      (*naluValues)[chunkIndex++] = make_unique<Nalu>(totalFrameLen, content);
   }

   return naluValues;
}

std::vector<std::string> H264FileReader::SplitByRegex(const std::string &inputString, const std::string &regEx)
{
   using namespace std;

   static regex reInstance{regEx};
   sregex_token_iterator start{inputString.begin(), inputString.end(), reInstance, {-1, 0}}, end;

   return vector<string>(start, end);
}
