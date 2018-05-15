/*
 *  Fuzzy Logic Operators Types and Symbolics
 *
 *  ./software/ch9/fuzzy.h
 *
 *  mtj@cogitollc.com
 *
 */

#ifndef _FUZZY_H
#define _FUZZY_H

typedef float fuzzyType;

fuzzyType fuzzyAnd( fuzzyType, fuzzyType );
fuzzyType fuzzyOr( fuzzyType, fuzzyType );
fuzzyType fuzzyNot( fuzzyType );

#endif /* _FUZZY_H */
