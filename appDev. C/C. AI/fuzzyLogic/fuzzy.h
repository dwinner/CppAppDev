//
// Fuzzy Logic Operators Types and Symbolics
//

#ifndef FUZZYLOGIC_FUZZY_H
#define FUZZYLOGIC_FUZZY_H

#include <assert.h>

#define MAX(a, b)   ((a>b) ? a : b)
#define MIN(a, b)   ((a<b) ? a : b)

/**
 * @brief Fuzzy type as float
 */
typedef float fuzzyType;

/**
 * @brief Fuzzy version of the AND operator.
 * @param lhs Left fuzzy value
 * @param rhs Right fuzzy value
 * @return Computed fuzzy value
 */
fuzzyType fuzzyAnd(fuzzyType lhs, fuzzyType rhs);

/**
 * @brief Fuzzy version of the OR operator.
 * @param lhs Left fuzzy value
 * @param rhs Right fuzzy value
 * @return Computed fuzzy value
 */
fuzzyType fuzzyOr(fuzzyType lhs, fuzzyType rhs);

/**
 * @brief Fuzzy version of the NOT operator.
 * @param fuzzyValue Fuzzy value
 * @return Inverse fuzzy value
 */
fuzzyType fuzzyNot(fuzzyType fuzzyValue);

#endif //FUZZYLOGIC_FUZZY_H
