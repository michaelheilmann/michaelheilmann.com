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
#include <assert.h>
#include "Arcadia/Ring1/Implementation/ToReal/result.h"
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

static inline Arcadia_Integer64Value
Arcadia_NumberLiteral_approximateExponent
  (
    Arcadia_Thread* thread,
    Arcadia_NumberLiteral* self,
    const char* p,
    Arcadia_BooleanValue* approximated
  )
{
  Arcadia_Integer64Value v = 0;
  Arcadia_SizeValue i, j;
  for (i = self->exponent.integral.start + self->exponent.integral.leadingZeroes.length, j = 0;
    i < self->exponent.integral.start + self->exponent.integral.leadingZeroes.length + self->exponent.integral.length && j < 19; ++i) {
    v = v * 10 + (p[i] - '0');
  }
  if (self->exponent.sign.length) {
    v = p[self->exponent.sign.start] == '-' ? -v : +v;
  }
  *approximated = i < self->exponent.integral.start + self->exponent.integral.leadingZeroes.length + self->exponent.integral.length;
  return v;
}

static inline Arcadia_Natural64Value
Arcadia_NumberLiteral_approximateSignificand
  (
    Arcadia_Thread* thread,
    Arcadia_NumberLiteral* self,
    const char* p,
    Arcadia_Integer64Value* exponent,
    Arcadia_BooleanValue* approximated
  )
{
  Arcadia_SizeValue integralDigitsCount = self->significand.integral.length - self->significand.integral.leadingZeroes.length; // The total number of integral digits (excluding leading zeroes).
  Arcadia_SizeValue fractionalDigitsCount = self->significand.fractional.length - self->significand.fractional.trailingZeroes.length; // The total number of fractional digits (excluding trailing zeroes).

  // If there are more then 19 digits in the significand, then we truncate the significand and recompute the exponent accordingly.
  Arcadia_Natural64Value significand1 = 0;
  Arcadia_Integer32Value exponent1 = 0;
  Arcadia_SizeValue i, n;
  for (n = 0, i = 0; n < 19 && i < integralDigitsCount; ++i, ++n) {
    significand1 = significand1 * 10 + (p[self->significand.integral.start + self->significand.integral.leadingZeroes.length + i] - '0');
  }
  if (i < integralDigitsCount) {
    // If not all integral digits were consumed and there are k integral digits left, we basically divide the number by 10^k and increase the exponent by k and set approximate to true.
    *approximated = true;
    exponent1 += integralDigitsCount - i;
    *exponent = exponent1;
    return significand1;
  } else {
    for (i = 0; n < 19 && i < fractionalDigitsCount; ++i, ++n) {
      significand1 = significand1 * 10 + (p[self->significand.fractional.start + i] - '0');
    }
    exponent1 = exponent1 - i;
    // If not all fractional digits were consumed and there are k fractional digits left, we set approximate to true.
    *approximated = i < fractionalDigitsCount;
    *exponent = exponent1;
    return significand1;
  }
}

#define withClinger (true)
#define withLemire (true)

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

  // Number within fast path bounds can be represented exactly.
  const Arcadia_Integer64Value MaximalExponent_Clinger = +22;
  const Arcadia_Integer64Value MinimalExponent_Clinger = -22;
#define MaximalDecimalSignificandDigits_Clinger 17
#define MaximalDecimalSignificandDigits_Lemire 19  

  if (!Arcadia_parseNumberLiteral(thread, &s.literal, p, n)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ConversionFailed);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_SizeValue totalIntegralDigits = s.literal.significand.integral.length - s.literal.significand.integral.leadingZeroes.length; // The total number of integral digits (excluding leading zeroes).
  Arcadia_SizeValue totalFractionalDigits = s.literal.significand.fractional.length - s.literal.significand.fractional.trailingZeroes.length; // The total number of fractional digits (excluding trailing zeroes).
  Arcadia_SizeValue totalExponentDigits = s.literal.exponent.integral.length - s.literal.exponent.integral.leadingZeroes.length; // The total number of exponent digits (excluding leading zeroes).
  Arcadia_SizeValue totalSignificandDigits = totalIntegralDigits + totalFractionalDigits;
  Arcadia_BooleanValue isSignificandNegative = s.literal.significand.sign.length ? '-' == p[s.literal.significand.sign.start] : false;
  Arcadia_BooleanValue isExponentNegative = s.literal.exponent.sign.length ? '-' == p[s.literal.exponent.sign.start] : false;


  // We have the big integers "exponent := 10^(e-|w|)" and "significant := vw".
  s.negative = isSignificandNegative;
  s.significand = Arcadia_NumberLiteral_approximateSignificand(thread, &s.literal, p, &s.shift, &s.significandTruncated);
  s.exponent = Arcadia_NumberLiteral_approximateExponent(thread, &s.literal, p, &s.exponentTruncated);

  // If the significand is zero, then the result is zero. The exponent does not matter anymore. [I]
  if (!s.significandTruncated && s.significand == Arcadia_Natural64Value_Literal(0)) {
    Arcadia_ToReal64_Result result;
    result.negative = s.negative;
    result.significand = Arcadia_Natural64Value_Literal(0);
    result.exponent = Arcadia_Integer32Value_Literal(0);
    Arcadia_Real64Value v;
    Arcadia_ToReal64_BitsToValue(thread, &v, &result);
    return v;
  }
  /* ~~ Clinger's method ~~ */
  if (withClinger) {
    if (!s.significandTruncated && !s.exponentTruncated && 
        totalSignificandDigits <= MaximalDecimalSignificandDigits_Clinger &&
        MinimalExponent_Clinger <= s.exponent && s.exponent <= MaximalExponent_Clinger) {
      Arcadia_Real64Value v = (Arcadia_Real64Value)s.significand;
      if (s.exponent >= 0) {
        v *= PowersOfTenReal64Value[+s.exponent];
      } else {
        v /= PowersOfTenReal64Value[-s.exponent];
      }
      return s.negative ? -v : +v;
    } else {
     // Cannot handle this. Resort to Lemire's method.
    }
  }
  /* ~~ Lemire's method ~~*/
  if (withLemire) {
    if (!s.exponentTruncated) {
      assert(!s.exponentTruncated);
      Arcadia_ToReal64_Result result;
      if (Arcadia_lemireReal64(thread, &result, &s)) {
        if (s.significandTruncated) {
          // Path to re-use Lemire's algorithm even if the number has too many digits in the significand a described in Lemire 2022.
          Arcadia_ToReal64_Result result1;
          State s1 = s;
          s1.significand += 1;
          if (Arcadia_lemireReal64(thread, &result1, &s1)) {
            if (result1.exponent != result.exponent || result1.negative != result.negative || result1.significand != result.significand) {
              // Cannot handle this. Report to Gay's method.
            } else {
              Arcadia_Real64Value v;
              Arcadia_ToReal64_BitsToValue(thread, &v, &result);
              return v;
            }
          }
        } else {
          Arcadia_Real64Value v;
          Arcadia_ToReal64_BitsToValue(thread, &v, &result);
          return v;
        }
      } else {
        // Cannot handle this. Report to Gay's method.
      }
    } else {
      // Cannot handle this. Report to Gay's method.
    }
  }
  /* ~~ Gay's method ~~ */
  Arcadia_ToReal64_Result result;
  if (Arcadia_gayReal64(thread, &result, p, n, &s.literal)) {
    Arcadia_Real64Value v;
    Arcadia_ToReal64_BitsToValue(thread, &v, &result);
    return v;
  }

  return 0.;

#pragma warning( pop )
}
