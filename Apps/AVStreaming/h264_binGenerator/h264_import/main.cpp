/**
 * Import script for H.264 file into header
 */

#include "H264FileReader.h"
#include "importGeneratorUtils.h"
#include <algorithm>
#include <fstream>
#include <memory>
#include <sstream>

void printUsage();

int main(int argc, const char *argv[])
{
    using namespace std;

    if (argc < 2)
    {
        printUsage();
        return EXIT_FAILURE;
    }

    const char *h264FileName = argv[1];
    unique_ptr<H264FileReader> h264FileReader = make_unique<H264FileReader>(h264FileName);
    unique_ptr<valarray<unique_ptr<Nalu>>> nalUnits = h264FileReader->GetNalUnits();
    size_t nalUnitsCount = nalUnits->size();

    const string headerFileName = string(h264FileName) + "_bin.h";
    ofstream fHeaderOut(headerFileName, ios_base::binary);

    // write include directives with header start
    string headerMarker(headerFileName);
    replaceAll(headerMarker, ".", "_");
    transform(headerMarker.begin(), headerMarker.end(), headerMarker.begin(), ::toupper);

    string prologue = genPrologue(nalUnitsCount, headerMarker);
    fHeaderOut << prologue;

    // Generate payload unit sizes
    string payloadUnitSizes = genPayloadUnitSizes(nalUnits);
    fHeaderOut << payloadUnitSizes;

    // Generate payload unit arrays
    string payloadUnitArrays = genPayloadUnitArrays(nalUnits);
    fHeaderOut << payloadUnitArrays;

    // Generate payload unit array of structures
    string payloadUnitStructArrays = genPayloadUnitStructArray(nalUnitsCount);
    fHeaderOut << payloadUnitStructArrays;

    // Write End header
    string epilogue = genEpilogue();
    fHeaderOut << epilogue;

    fHeaderOut.close();

    return EXIT_SUCCESS;
}

void printUsage()
{
    fprintf(stderr, "import_h264 H264-file");
}
