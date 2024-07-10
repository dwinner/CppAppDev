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
typedef float FuzzyBoolT;

/**
 * @brief Fuzzy version of the AND operator.
 * @param lhs Left fuzzy value
 * @param rhs Right fuzzy value
 * @return Computed fuzzy value
 */
FuzzyBoolT fuzzyAnd(FuzzyBoolT lhs, FuzzyBoolT rhs);

/**
 * @brief Fuzzy version of the OR operator.
 * @param lhs Left fuzzy value
 * @param rhs Right fuzzy value
 * @return Computed fuzzy value
 */
FuzzyBoolT fuzzyOr(FuzzyBoolT lhs, FuzzyBoolT rhs);

/**
 * @brief Fuzzy version of the NOT operator.
 * @param fuzzyValue Fuzzy value
 * @return Inverse fuzzy value
 */
FuzzyBoolT fuzzyNot(FuzzyBoolT fuzzyValue);

#endif //FUZZYLOGIC_FUZZY_H
