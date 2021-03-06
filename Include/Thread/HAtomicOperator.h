/**
*@file HAtomicOperator.h
*@brief This file defined a utility for atomic operations.
*@author antmuse@live.cn
*@date 2014-09-22
*/

#ifndef APP_HATOMICOPERATOR_H
#define APP_HATOMICOPERATOR_H

#include "HConfig.h"


namespace app {
void AppAtomicReadBarrier();

void AppAtomicWriteBarrier();

void AppAtomicReadWriteBarrier();

/**
*@brief s32 iTarget |= value;
*/
s32 AppAtomicFetchOr(s32 value, s32* iTarget);
s16 AppAtomicFetchOr(s16 value, s16* iTarget);


/**
*@brief s32 iTarget ^= value;
*/
s32 AppAtomicFetchXor(s32 value, s32* iTarget);
s16 AppAtomicFetchXor(s16 value, s16* iTarget);


/**
*@brief s32 iTarget &= value;
*/
s32 AppAtomicFetchAnd(s32 value, s32* iTarget);
s16 AppAtomicFetchAnd(s16 value, s16* iTarget);


/**
*@param iTarget A pointer to the value to be incremented,
*must be aligned on a 32-bit boundary; otherwise, See _aligned_malloc().
*@return The resulting incremented value.
*/
s32 AppAtomicIncrementFetch(s32* it);


/**
*@param iTarget A pointer to the value to be incremented,
*must be aligned on a 64-bit boundary; otherwise, See _aligned_malloc().
*@return The resulting incremented value.
*/
s64 AppAtomicIncrementFetch(s64* it);
s16 AppAtomicIncrementFetch(s16* it);


/**
*@param iTarget A pointer to the value to be decremented.
*must be aligned on a 32-bit boundary; otherwise, See _aligned_malloc().
*@return The resulting decremented value.
*/
s32 AppAtomicDecrementFetch(s32* it);


/**
*@param iTarget A pointer to the value to be decremented.
*must be aligned on a 64-bit boundary; otherwise, See _aligned_malloc().
*@return The resulting decremented value.
*/
s64 AppAtomicDecrementFetch(s64* it);
s16 AppAtomicDecrementFetch(s16* it);


/**
*@brief The function AppAtomicFetchAdd target with a new value, AppFetchAnd returns its prior value.
*@param addValue New value.
*@param iTarget A pointer to the value to be added.
*@return The prior value of the iTarget parameter.
*/
s32 AppAtomicFetchAdd(s32 addValue, s32* iTarget);

/**
*@brief The function sets this variable to new value, AppFetchAnd returns its prior value.
*@param newValue New value.
*@param iTarget A pointer to the value to be exchanged.
*@return The prior value of the iTarget parameter.
*/
s32 AppAtomicFetchSet(s32 newValue, s32* iTarget);
void* AppAtomicFetchSet(void* value, void** iTarget);
s64 AppAtomicFetchSet(s64 value, s64* iTarget);


/**
*@brief The function sets this variable to new value, AppFetchAnd returns its prior value.
*@param newValue New value.
*@param iTarget A pointer to the value to be set.
*@param comparand A value to be compared.
*@return The prior value of the iTarget parameter.
*/
s32 AppAtomicFetchCompareSet(s32 newValue, s32 comparand, s32* iTarget);
s64 AppAtomicFetchCompareSet(s64 newValue, s64 comparand, s64* iTarget);


s32 AppAtomicFetch(s32* iTarget);
s64 AppAtomicFetch(s64* iTarget);
} //end namespace app

#endif	// APP_HATOMICOPERATOR_H
