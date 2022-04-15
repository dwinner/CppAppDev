#include "H264FileReader.h"
#include "sysdef/sysdef.h"
//#include <cassert>
//#include <cstdio>
//#include <cstdlib>
#include <gtest/gtest.h>
//#include <iostream>
#include <memory>
//#include <string>

TEST(Analyzing_H264, H264_READER)
{
    const auto h264TestFile = "JM_cqm_cabac.264";
    using namespace std;

    string error;
    unique_ptr<H264FileReader> h264FileReader = make_unique<H264FileReader>(h264TestFile);
    unique_ptr<valarray<unique_ptr<Nalu>>> nalUnits = h264FileReader->GetNalUnits(error);
    size_t nalUnitsCount = nalUnits->size();

    EXPECT_TRUE(error.empty());
    EXPECT_GT(nalUnitsCount, 0);

    // check the expected NALU count
    const size_t expectedNaluCount = 102;
    EXPECT_EQ(nalUnitsCount, expectedNaluCount);

    int64_t totalBytesCount = 0;
    for (size_t nalIdx = 0; nalIdx < nalUnitsCount; nalIdx++)
    {
        unique_ptr<Nalu> naluItem = move((*nalUnits)[nalIdx]);
        size_t length = naluItem->GetLength();
        std::valarray<uint8_t> content = naluItem->GetContent();

        // Check that AUD has 00 00 00 01 in the 1st 4 elements
        uint8_t byte1 = content[0];
        uint8_t byte2 = content[1];
        uint8_t byte3 = content[2];
        uint8_t byte4 = content[3];

        const auto zeroByte = static_cast<uint8_t>(0);
        const auto oneByte = static_cast<uint8_t>(1);

        EXPECT_EQ(byte1, zeroByte);
        EXPECT_EQ(byte2, zeroByte);
        EXPECT_EQ(byte3, zeroByte);
        EXPECT_EQ(byte4, oneByte);

        totalBytesCount += length;
    }

    // Check that all binary data has been analyzed
    FILE* h264FileDesc;
    errno_t errorNum = fopen_s(&h264FileDesc, h264TestFile, "rb");
    EXPECT_EQ(errorNum, 0);

    fseek(h264FileDesc, 0, SEEK_END);
    const int64_t fileSize = ftell(h264FileDesc);
    fseek(h264FileDesc, 0, SEEK_SET);

    EXPECT_EQ(totalBytesCount, fileSize);
}
