// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
//
// Permission to use, copy, modify, and distribute this software for any
// purpose without fee is hereby granted, provided that this entire notice
// is included in all copies of any software which is or includes a copy
// or modification of this software and in all copies of the supporting
// documentation for such software.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
// REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

// Last modified: 2025-03-07

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/ToReal/toReal64.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Implementation/ToReal/gay.h"
#include "Arcadia/Ring1/Implementation/ToReal/lemire.h"

static Arcadia_Integer64Value
decimalDigitsToInteger64Value
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value* decimalDigits,
    Arcadia_SizeValue length
  );

static const Arcadia_Real64Value PowersOfTenReal64Value[] = {
  1e0,    // 10^0
  1e1,    // 10^1
  1e2,    // 10^2
  1e3,    // 10^3
  1e4,    // 10^4
  1e5,    // 10^5
  1e6,    // 10^6
  1e7,    // 10^7
  1e8,    // 10^8
  1e9,    // 10^9
  1e10,   // 10^10
  1e11,   // 10^11
  1e12,   // 10^12
  1e13,   // 10^13
  1e14,   // 10^14
  1e15,   // 10^15
  1e16,   // 10^16
  1e17,   // 10^17
  1e18,   // 10^18
  1e19,   // 10^19
  1e20,   // 10^20
  1e21,   // 10^21
  1e22,   // 10^22
};

static Arcadia_Integer64Value
decimalDigitsToInteger64Value
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value* decimalDigits,
    Arcadia_SizeValue length
  )
{
  Arcadia_BigInteger* q = Arcadia_BigInteger_create(thread);
  for (Arcadia_SizeValue i  = 0, n = length; i < n; ++i) {
    Arcadia_Natural8Value digit = (Arcadia_Natural8Value)decimalDigits[i] - (Arcadia_Natural8Value)'0';
    Arcadia_BigInteger_multiplyInteger8(thread, q, 10);
    Arcadia_BigInteger_addInteger8(thread, q, digit);
  }
  return Arcadia_BigInteger_toInteger64(thread, q);
}

#if 0
Arcadia_BooleanValue
shouldRoundUp 
  (
    Arcadia_Thread* thread,
    Arcadia_BooleanValue leastSignificandBit,
    Arcadia_BooleanValue roundBit,
    Arcadia_BooleanValue hasNonZeroTailBits
  )
{
  return roundBit && (hasNonZeroTailBits || leastSignificandBit);
}

// hasZeroFractionalPart if the fractional part is not present/consists of all zeroes
Arcadia_Natural64Value
rightShiftWithRounding
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value integralValue,
    Arcadia_Natural64Value shift,
    Arcadia_BooleanValue hasZeroTail
  )
{ 
  if (shift < 1) {

  }
  if (shift >= 64) {
    // If we need to shift further than it is possible to shift, then answer is always zero.
    return Arcadia_Natural64Value_Literal(0);
  }
  // Mask of the bits shifted out.
  Arcadia_Natural64Value extraBitsMask = (Arcadia_Natural64Value_Literal(1) << (shift - 1)) - 1;
  // Mask of the highest bit shifted out.
  Arcadia_Natural64Value roundBitMask = (Arcadia_Natural64Value_Literal(1) << (shift - 1));
  // Mask of the new least significand bit.
  Arcadia_Natural64Value leastSignificandBitMask = (Arcadia_Natural64Value_Literal(1) << shift);

  Arcadia_BooleanValue leastSignificandBit = 0 != (integralValue & leastSignificandBitMask);
  Arcadia_BooleanValue roundBit = 0 != (integralValue & roundBitMask);
  Arcadia_BooleanValue hasNonZeroTailBits  = !hasZeroTail || (integralValue & extraBitsMask);
  
  return (integralValue >> shift) + (shouldRoundUp(thread, leastSignificandBit, roundBit, hasNonZeroTailBits) ? Arcadia_Natural64Value_Literal(1) : Arcadia_Natural64Value_Literal(0));
  
}

Arcadia_Real64Value
natural64ToReal64
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value significand,
    Arcadia_Integer64Value exponent
  )
{
  Arcadia_Integer64Value initialExponent = exponent;
  Arcadia_SizeValue significandBits = Arcadia_countSignificandBitsNatural64Value(thread, significand);
  // We have a bit sequence w representing w := [w[n-1], ..., w[0]] with w[n-1] = 1.
  // We have in the FP significand the bits b[52], b[51], ..., b[0] where b[52] is implicit and not stored.
  // Assume w is smaller than or equal to the 52 Bits available, then we need to shift them to the left by 52 - |w| >= 0 for that b[52] = w[n-1].
  // Assume w is greater than 52 Bits available, then we need to shift them to the right by 52 - |w| < 0. b[52] = w[n-1] (dropping the shifted out bits).
  Arcadia_Integer64Value significandShift = 52 - significandBits;
  // To make up for that shift, we need to subtract that shift from the exponent.
  Arcadia_Integer64Value adjustedExponent = initialExponent - (Arcadia_Integer64Value)significandBits;
  if (adjustedExponent > Arcadia_Real64Value_MaximalExponent) {
    // Exponent is too big.
    return Arcadia_Real64Value_PositiveInfinity;
  } else if (adjustedExponent < Arcadia_Real64Value_MinimalExponent) {
    // Exponent is too small.
    // Try denormalized number.
    // We pack the exponent into the significand. Furthermore, we add in the exponent bias minus -1 (as there is no implicit 1 bit anymore).
    Arcadia_Integer64Value denormalizedSignificandShift = significandShift + adjustedExponent + Arcadia_Real64Value_ExponentBias - 1;
    // The exponent of a denormalized number has a biased exponent of 0.
    // Hence the unbiased exponent is -bias.
    adjustedExponent = -Arcadia_Real64Value_ExponentBias;
    if (denormalizedSignificandShift < 0) {
      // Use two steps for right shifts:
      // For a shift of N bits, we first shift by N-1 bits, then shift the last bit and use its value to round the significand.
    }
  }
}

// w.0 is mapped to 0.w * 10^|w|
Arcadia_Real64Value
bigIntegerToReal64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{
  Arcadia_SizeValue bitsOfPrecision = Arcadia_BigInteger_countSignificandBits(thread, self);
  // If we have less than 64 bits or precision, we can actually generate an uint64_t out of it.
  if (bitsOfPrecision <= 64) {
    Arcadia_Natural64Value selfInteger64 = Arcadia_BigInteger_toNatural64(thread, self);
  }
  return 0.;
}
#endif

#include <assert.h>
#include "Arcadia/Ring1/Implementation/ToReal/result.h"

Arcadia_Real64Value
Arcadia_toReal64
  (
    Arcadia_Thread* thread,
    const Arcadia_Natural8Value *p,
    Arcadia_SizeValue n
  )
{
#pragma warning( push )
#pragma warning( disable : 4189)

  State s;

  const Arcadia_SizeValue explicitSignificandBits = 52;
  const Arcadia_SizeValue significandBits = explicitSignificandBits + 1;

  // Number within fast path bounds can be represented exactly.
  const Arcadia_Integer64Value MaximalExponent_Clinger = +22;
  const Arcadia_Integer64Value MinimalExponent_Clinger = -22;
#define MaximalDecimalSignificandDigits_Clinger 17
#define MaximalDecimalSignificandDigits_Lemire 19  

  // 10^19 is the maximal power of 10 representable by a uint64_t.
  // UINT64_MAX = 18446744073709551615
  //              10000000000000000000
  // Obviously, any decimal of less than 19 digits can be represented by an uint64_t.
  //const Arcadia_Integer64Value maximalDecimalDigitsFastPath = 19 - 1;
  // 10^18 is the maximum power of 10 representalb by an int64_t.
  // INT64_MAX = 9223372036854775807
  //             1000000000000000000
  //                9007199254740992
  // Obviously, any decimal of less than 18 digits can be represented by an int64_t.
  const Arcadia_Integer64Value maximalDecimalDigitsFastPath = 18 - 1;
  // This is 2^53.
  const Arcadia_Integer64Value maximalSignificandFastPath = Arcadia_Integer64Value_Literal(1) << significandBits;

  if (!Arcadia_parseNumberLiteral(thread, &s.literal, p, n)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_SizeValue totalSignificandDigits = 0;
  Arcadia_SizeValue totalIntegralDigits = s.literal.significand.integral.length - s.literal.significand.integral.leadingZeroes.length;
  Arcadia_SizeValue totalFractionalDigits = s.literal.significand.fractional.length - s.literal.significand.fractional.trailingZeroes.length;
  totalSignificandDigits += totalIntegralDigits;
  totalSignificandDigits += totalFractionalDigits;

  // Given v.w * 10^e, compute vw. 10^(e-|w|).
  // Put vw into a big integer "significand" and 10^(e-|w|) into a big integer "exponent".
  s.exponent = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setZero(thread, s.exponent);
  if (s.literal.exponent.length) {
    Arcadia_BigInteger_setDecimalDigits(thread, s.exponent, p + s.literal.exponent.integral.start + s.literal.exponent.integral.leadingZeroes.length,
      s.literal.exponent.integral.length);
    if (s.literal.exponent.sign.length) {
      if (p[s.literal.exponent.sign.start] == '-') {
        Arcadia_BigInteger_multiplyInteger8(thread, s.exponent, -1);
      }
    }
  } else {
    // If no exponent is specified, the exponent is 0.
  }
  s.significand = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setZero(thread, s.significand);
  if (totalIntegralDigits) {
    Arcadia_BigInteger_setDecimalDigits(thread, s.significand, p + s.literal.significand.integral.start + s.literal.significand.integral.leadingZeroes.length,
                                        s.literal.significand.integral.length - s.literal.significand.integral.leadingZeroes.length);
  }
  if (totalFractionalDigits) {
    Arcadia_BigInteger* temporary = Arcadia_BigInteger_create(thread);
    Arcadia_BigInteger_setPowerOfTenNatural64(thread, temporary, totalFractionalDigits);
    Arcadia_BigInteger_multiply(thread, s.significand, temporary);
    Arcadia_BigInteger_setDecimalDigits(thread, temporary, p + s.literal.significand.fractional.start,
                                        s.literal.significand.fractional.length - s.literal.significand.fractional.trailingZeroes.length);
    Arcadia_BigInteger_add(thread, s.significand, temporary);
    Arcadia_BigInteger_subtractInteger64(thread, s.exponent, totalFractionalDigits);
  }
  // We have the big integers "exponent := 10^(e-|w|)" and "significant := vw".
  s.negative = s.literal.significand.sign.length ? p[s.literal.significand.sign.start] == '-' : false;

  // [1] Trivial cases.

  // If the significand is zero, then the result is zero. The exponent does not matter anymore.
  if (Arcadia_BigInteger_isZero(thread, s.significand)) {
    Arcadia_ToReal64_Result result;
    result.negative = s.negative;
    result.significand = Arcadia_Natural64Value_Literal(0);
    result.exponent = Arcadia_Integer32Value_Literal(0);
    Arcadia_Real64Value v;
    Arcadia_ToReal64_BitsToValue(thread, &v, &result);
    return v;
  }
  // If the exponent is smaller than -324 (-45) for double (float), then the result is zero.
  if (Arcadia_BigInteger_lowerThanInteger32(thread, s.exponent, -324)) {
    Arcadia_ToReal64_Result result;
    result.negative = s.negative;
    result.significand = Arcadia_Natural64Value_Literal(0);
    result.exponent = Arcadia_Integer32Value_Literal(0);
    Arcadia_Real64Value v;
    Arcadia_ToReal64_BitsToValue(thread, &v, &result);
    return v;
  }
  // If the exponent is greater than +308 (+38) for double (float), then the result is infinity.
  if (Arcadia_BigInteger_greaterThanInteger32(thread, s.exponent, +308)) {
    return s.negative ? Arcadia_Real64Value_NegativeInfinity : Arcadia_Real64Value_PositiveInfinity;
  }

  assert(Arcadia_BooleanValue_False == Arcadia_BigInteger_isZero(thread, s.significand));
  assert(Arcadia_BooleanValue_True == Arcadia_BigInteger_greaterThanOrEqualToInteger32(thread, s.exponent, -324));
  assert(Arcadia_BooleanValue_True == Arcadia_BigInteger_lowerThanOrEqualToInteger32(thread, s.exponent, +308));

  // An exponent [-324, +308] certainly fits into an Integer64.
  s.exponentInteger64 = Arcadia_BigInteger_toInteger64(thread, s.exponent);

  /* ~~ Clinger's method ~~ */
  if (totalSignificandDigits <= MaximalDecimalSignificandDigits_Clinger && MinimalExponent_Clinger <= s.exponentInteger64 && s.exponentInteger64 <= MaximalExponent_Clinger) {
    // We can safely convert the significand into a Natural64 value is it has not more than MaximalDecimalSignificandDigits_Clinger <= 19 digits.
    s.significandNatural64 = Arcadia_BigInteger_toNatural64WithTruncation(thread, s.significand, &s.truncated);
    assert(Arcadia_BooleanValue_False == s.truncated);
    Arcadia_Real64Value v = (Arcadia_Real64Value)s.significandNatural64;
    if (s.exponentInteger64 >= 0) {
      v *= PowersOfTenReal64Value[+s.exponentInteger64];
    } else {
      v /= PowersOfTenReal64Value[-s.exponentInteger64];
    }
    return s.negative ? -v : +v;
  } else {
   // Cannot handle this. Resort to Lemire's method.
  }
  /* ~~ Lemire's method ~~*/
  if (totalSignificandDigits <= MaximalDecimalSignificandDigits_Lemire) {
    // We can safely convert the significand into a Natural64 value is it has not more than MaximalDecimalSignificandDigits_Lemire <= 19 digits.
    s.significandNatural64 = Arcadia_BigInteger_toNatural64WithTruncation(thread, s.significand, &s.truncated);
    assert(Arcadia_BooleanValue_False == s.truncated);
    Arcadia_ToReal64_Result result;
    if (Arcadia_lemireReal64(thread, &result, &s)) {
      Arcadia_Real64Value v;
      Arcadia_ToReal64_BitsToValue(thread, &v, &result);
      return v;
    } else {
      // Cannot handle this. Report to Gay's method.
    }
  }
  /* ~~ Gay's method ~~ */
  Arcadia_ToReal64_Result result;
  s.significandNatural64 = Arcadia_BigInteger_toNatural64WithTruncation(thread, s.significand, &s.truncated);
  if (Arcadia_gayReal64(thread, &result, &s)) {
    Arcadia_Real64Value v;
    Arcadia_ToReal64_BitsToValue(thread, &v, &result);
    return v;
  }

  return 0.;

#pragma warning( pop )
}
