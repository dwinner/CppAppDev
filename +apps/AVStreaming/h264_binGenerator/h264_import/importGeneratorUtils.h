#ifndef H264_IMPORT_IMPORTGENERATORUTILS_H
#define H264_IMPORT_IMPORTGENERATORUTILS_H

#include <string>
#include <valarray>
#include "Nalu.h"

/**
 * Replace all string occurrences
 * @param str Source string to modify
 * @param from String to replace From
 * @param to String to replace To
 */
void replaceAll(std::string &str, const std::string &from, const std::string &to);

/**
 * Generate Prologue for C' header
 * @param nalUnitsCount Count on NAL units
 * @param headerMarker The header marker for 'include once'
 * @return String for Prologue for C' header
 */
std::string genPrologue(size_t nalUnitsCount, const std::string &headerMarker);

/**
 * Generate Payload unit sizes
 * @param nalUnits NAL units
 * @return String for Payload unit sizes
 */
std::string genPayloadUnitSizes(std::unique_ptr<std::valarray<std::unique_ptr<Nalu>>> &nalUnits);

/**
 * Generate C' array of payload unit data
 * @param nalUnits NAL units
 * @return String for C' array of payload unit data
 */
std::string genPayloadUnitArrays(const std::unique_ptr<std::valarray<std::unique_ptr<Nalu>>> &nalUnits);

/**
 * Generate C' array of structures with payload units
 * @param nalUnitsCount Count on NAL units
 * @return String for C' array of structures with payload units
 */
std::string genPayloadUnitStructArray(size_t nalUnitsCount);

/**
 * Generate Epilogue for C' header
 * @return String for Epilogue for C' header
 */
std::string genEpilogue();

#endif //H264_IMPORT_IMPORTGENERATORUTILS_H
