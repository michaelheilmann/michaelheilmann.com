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

// Last modified: 2024-09-27

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/ToReal/gay.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Implementation/ToReal/result.h"

// When perform a decimal to binary conversion,
// then this is the maximum number of decimal digits in the significand we accept during parsing.
// https://www.exploringbinary.com/maximum-number-of-decimal-digits-in-binary-floating-point-numbers/
// determines 767 digits. We add two more digits and obtain 769 digits. This is also the value used by https://github.com/fastfloat.
#define Arcadia_Real64Value_MaximumNumberOfParsedDecimalDigits (769)

// When perform a deciaml digit to binary conversion, 
// then this is the maximum number of decimal digits in the significand we are accepting during parsing.
// https://www.exploringbinary.com/maximum-number-of-decimal-digits-in-binary-floating-point-numbers/
// determines 112 digits. We add two more digits and obtain 114 digits. This is also the value used by https://github.com/fastfloat.
#define Arcadia_Real32Value_MaximumNumberOfParsedDecimalDigits (114)

Arcadia_BooleanValue
Arcadia_gayReal64
  (
    Arcadia_Thread* thread,
    Arcadia_ToReal64_Result* result,
    State* state
  )
{
  if (state->truncated) {
    Arcadia_BigInteger* powerOfTen = Arcadia_BigInteger_create(thread);
    Arcadia_BigInteger_setPowerOfTenNatural8(thread, powerOfTen, 10);
    Arcadia_BigInteger_multiply(thread, state->significand, powerOfTen);
    Arcadia_BigInteger_addNatural8(thread, state->significand, 1);
  }
#if 0
  const Arcadia_SizeValue normalMantissaBits = significandBits; // including the implicit bit

  //const Arcadia_SizeValue overflowDecimalExponent = (maximalExponent + (2 * significandLength)) / 3;

  // To generate an N Bit mantissa we required N + 1 Bits of precision.
  //The extra bit is used to correctly round the mantissa. If there are fewer bits than this available, then this is ok: in that case the bits that are available are used and no round is required.
  const Arcadia_SizeValue requiredBitsOfPrecision = normalMantissaBits + 1;

  //Arcadia_SizeValue integerDigitsMissing = /*positive exponent*/ - (number.significand.integral.length - number.significand.integral.leadingZeroes.length);

  // Accumulate the integral digits (without leading zeroes) into a big integer.
  Arcadia_BigInteger* integral = Arcadia_BigInteger_create(thread);
  if (totalIntegralDigits) {
    Arcadia_BigInteger_setDecimalDigits(thread, integral, p + s.literal.significand.integral.start + s.literal.significand.integral.leadingZeroes.length,
      s.literal.significand.integral.length - s.literal.significand.integral.leadingZeroes.length);
// Now we need to subtract the number of decimal digits added from the exponent.
// Because v.w must become 0.vw.
    Arcadia_BigInteger_subtractNatural64(thread, s.exponent, s.literal.significand.integral.length - s.literal.significand.integral.leadingZeroes.length);
  }
  // Determine the bits of precision we achieved so far.
  Arcadia_SizeValue integralBitsOfPrecision = Arcadia_BigInteger_countSignificandBits(thread, integral);
  if (integralBitsOfPrecision >= requiredBitsOfPrecision || s.literal.significand.fractional.length == 0) {
    return 0.;
  }
  // The value contains the integer part.
  // If [1] this number has more than the required number of bits pr precision or [2] the mantissa has no fractional part, then we can return the result.
  if (integralBitsOfPrecision >= requiredBitsOfPrecision || s.literal.significand.fractional.length == 0) {
    return 0.;
  }
  // Otherwise we did not get enough bits of precision from the integer part, and the mantissa has a fractional part.
  // We parse the fractional part of the mantissa to obtain more bits of precision.
  // That is, we compute an integer N which is the sequence of digits of the fractional part.
  // Next, we compute a negative power of ten such that N/M is equal to the fractional part of the mantissa.
  //Arcadia_SizeValue fractionalDenominator = number.significand.fractional.length - number.significand.fractional.trailingZeroes.length;
  return 0.;
#endif
  result->significand = Arcadia_Natural64Value_Literal(0);
  result->exponent = Arcadia_Integer32Value_Literal(0);
  result->negative = state->negative;
  return Arcadia_BooleanValue_False;
}
