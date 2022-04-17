#include <sstream>
#include "importGeneratorUtils.h"

std::string genEpilogue()
{
    std::ostringstream strOut;

    strOut << "#ifdef __cplusplus" << std::endl;
    strOut << "};" << std::endl;
    strOut << "#endif" << std::endl;
    strOut << std::endl;
    strOut << "#endif" << std::endl;
    strOut << std::endl;

    return strOut.str();
}

std::string genPayloadUnitStructArray(size_t nalUnitsCount)
{
    std::ostringstream strOut;

    strOut << "struct VIDEORTP_payloadUnit_t payloadUnits[PAYLOAD_UNIT_SIZE] = " << std::endl;
    strOut << "{" << std::endl;
    for (size_t nalIdx = 0; nalIdx < nalUnitsCount; nalIdx++)
    {
        strOut << "\t"
                   << "{ "
                   << "payloadUnitData" << (nalIdx + 1) << ", "
                   << "PAYLOAD_UNIT_SIZE_" << (nalIdx + 1)
                   << " }";
        if (nalIdx != nalUnitsCount - 1)
        {
            strOut << ",";
        }

        strOut << std::endl;
    }

    strOut << "};" << std::endl;
    strOut << std::endl;

    return strOut.str();
}

std::string genPayloadUnitArrays(const std::unique_ptr<std::valarray<std::unique_ptr<Nalu>>> &nalUnits)
{
    std::ostringstream strOut;

    for (size_t nalIdx = 0; nalIdx < nalUnits->size(); nalIdx++)
    {
        std::unique_ptr<Nalu> naluItem = move((*nalUnits)[nalIdx]);
        std::valarray<uint8_t> content = naluItem->GetContent();

        strOut << "static const uint8_t payloadUnitData" << (nalIdx + 1)
                   << "[" << "PAYLOAD_UNIT_SIZE_" << (nalIdx + 1) << "] = { ";
        for (size_t byteIdx = 0; byteIdx < content.size(); byteIdx++)
        {
            strOut << static_cast<size_t>(content[byteIdx]);
            if (byteIdx != content.size() - 1)
            {
                strOut << ",";
            }
        }

        strOut << " };" << std::endl;

        (*nalUnits)[nalIdx] = move(naluItem);
    }

    strOut << std::endl;

    return strOut.str();
}

std::string genPayloadUnitSizes(std::unique_ptr<std::valarray<std::unique_ptr<Nalu>>> &nalUnits)
{
    std::ostringstream strOut;

    for (size_t nalIdx = 0; nalIdx < nalUnits->size(); nalIdx++)
    {
        std::unique_ptr<Nalu> naluItem = move((*nalUnits)[nalIdx]);
        size_t length = naluItem->GetLength();
        strOut << "#define PAYLOAD_UNIT_SIZE_" << (nalIdx + 1) << "  " << length << std::endl;
        (*nalUnits)[nalIdx] = move(naluItem);
    }

    strOut << std::endl;

    return strOut.str();
}

std::string genPrologue(size_t nalUnitsCount, const std::string &headerMarker)
{
    std::ostringstream strOut;

    strOut << "#ifndef " << headerMarker << std::endl;
    strOut << "#define " << headerMarker << std::endl;
    strOut << std::endl;

    strOut << "#ifdef __cplusplus" << std::endl;
    strOut << "extern \"C\"" << std::endl;
    strOut << "{" << std::endl;
    strOut << "#endif" << std::endl;
    strOut << std::endl;

    strOut << "#include \"ProgramTableGeneration/PayloadUnitSequenceRepeater.h\"" << std::endl;
    strOut << "#include <stdint.h>" << std::endl << std::endl;

    strOut << "#define PAYLOAD_UNIT_SIZE " << nalUnitsCount << std::endl << std::endl;

    return strOut.str();
}

void replaceAll(std::string &str, const std::string &from, const std::string &to)
{
    if (from.empty())
    {
        return;
    }

    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);

        // In case 'to' contains 'from', like replacing 'x' with 'yx'
        start_pos += to.length();
    }
}