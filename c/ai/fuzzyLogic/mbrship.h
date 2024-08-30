//
// Fuzzy Logic Membership Functions
//

#ifndef FUZZYLOGIC_MBRSHIP_H
#define FUZZYLOGIC_MBRSHIP_H

#include "fuzzy.h"

#define TRICKLE_CHARGE	0
#define FAST_CHARGE	1

/**
 * @brief Normalize the fuzzy logic value.
 * @param in Fuzzy value
 * @return Normalized fuzzy value
 */
int normalize(FuzzyBoolT in);

/**
 * @brief Return the fuzzified value given the spike profile.
 * @param value Value
 * @param lo Low range
 * @param high High range
 * @return Fuzzified value
 */
FuzzyBoolT spikeProfile(float value, float lo, float high);

/**
 * @brief Return the fuzzified value given the plateau profile.
 * @param value Value
 * @param lo Low range
 * @param loPlat Low plat range
 * @param hiPlat High pla range
 * @param hi High range
 * @return
 */
FuzzyBoolT plateauProfile(float value, float lo, float loPlat, float hiPlat, float hi);

/**
 * @brief Return the fuzzified value using the hot (temperature)
 *  membership function. The hot membership function uses
 *  the plateau profile.
 * @param temperature Temperature
 * @return Fuzzified temperature value
 */
FuzzyBoolT mTempHot(float temperature);

/**
 * @brief Return the fuzzified value using the warm (aTemperature)
 *  membership function.  The warm membership function uses
 *  the plateau profile.
 * @param aTemperature Temperature
 * @return Fuzzified aTemperature value
 */
FuzzyBoolT mTempWarm(float aTemperature);

/**
 * @brief Return the fuzzified value using the cold (temperature)
 *  membership function.  The cold membership function uses
 *  the plateau profile.
 * @param temperature Temperature
 * @return Fuzzified temperature value
 */
FuzzyBoolT mTempCold(float temperature);

/**
 * @brief Return the fuzzified value using the low (voltage)
 *  membership function.  The low membership function uses
 *  the plateau profile.
 * @param voltage Voltage
 * @return Fuzzified voltage value
 */
FuzzyBoolT mVoltageLow(float voltage);

/**
 * @brief Return the fuzzified value using the medium (voltage)
 *  membership function.  The medium membership function
 *  uses the plateau profile.
 * @param voltage Voltage
 * @return Fuzzified voltage value
 */
FuzzyBoolT mVoltageMedium(float voltage);

/**
 * @brief Return the fuzzified value using the high (voltage)
 *  membership function.  The high membership function
 *  uses the plateau profile.
 * @param voltage Voltage
 * @return Fuzzified voltage value
 */
FuzzyBoolT mVoltageHigh(float voltage);

#endif //FUZZYLOGIC_MBRSHIP_H
