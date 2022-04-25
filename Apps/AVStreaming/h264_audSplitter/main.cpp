#include "H264FileReader.h"
#include <iostream>
#include <type_traits>
#include <cassert>

int main()
{
   const auto h264TestFile = "test_noloop.h264";

   using namespace std;

   unique_ptr<H264FileReader> h264FileReader = make_unique<H264FileReader>(h264TestFile);
   unique_ptr<valarray<unique_ptr<Nalu>>> nalUnits = h264FileReader->GetNalUnits();
   size_t nalUnitsCount = nalUnits->size();

   assert(nalUnitsCount > 0);

   // check the expected NALU count
   const size_t expectedNaluCount = 145;
   assert(nalUnitsCount == expectedNaluCount);

   for (size_t nalIdx = 0; nalIdx < nalUnitsCount; nalIdx++)
   {
      unique_ptr<Nalu> naluItem = move((*nalUnits)[nalIdx]);
      size_t length = naluItem->GetLength();
      std::valarray<uint8_t> content = naluItem->GetContent();

      // Check that marker has 00 00 00 01 in the 1st 4 elements
      uint8_t byte1 = content[0];
      uint8_t byte2 = content[1];
      uint8_t byte3 = content[2];
      uint8_t byte4 = content[3];

      const auto zeroByte = static_cast<uint8_t>(0);
      const auto oneByte = static_cast<uint8_t>(1);

      assert(byte1 == zeroByte);
      assert(byte2 == zeroByte);
      assert(byte3 == zeroByte);
      assert(byte4 == oneByte);

      // Check that AUD has 09 at the 5th byte
      uint8_t byte5 = content[4];
      assert(byte5 == static_cast<uint8_t>(9));

      cout << "Length: " << length << endl;
      cout << "Content: " << endl;
      for (size_t i = 0; i < length; i++)
      {
         printf(" %02x", content[i]);
         if ((i + 1) % 16 == 0)
         {
            cout << endl;
         }
      }

      cout << endl << endl;
   }

   return 0;
}