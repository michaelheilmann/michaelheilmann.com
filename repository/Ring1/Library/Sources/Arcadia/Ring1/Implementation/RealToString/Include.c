// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/RealToString/Include.h"

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Real32_getBits.h"
#include "Arcadia/Ring1/Implementation/Real64_getBits.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"

// See
// - Ulf Adams. 2018. Ryu: Fast Float-to-String Conversion. SIGPLAN Not. 53, 4 (April 2018), 270–282. https://doi.org/10.1145/3296979.3192369
// - https://github.com/ulfjack/ryu

static Arcadia_Natural8Value nanString[] = u8"<not a number>";
static Arcadia_Natural8Value positiveInfinityString[] = u8"<positive infinity>";
static Arcadia_Natural8Value negativeInfinityString[] = u8"<negative infinity>";
static Arcadia_Natural8Value positiveZero[] = u8"+0";
static Arcadia_Natural8Value negativeZero[] = u8"-0";

#include <assert.h>

// Returns floor(log_10(2^e)); requires 0 <= e <= 1650.
static inline uint32_t log10Pow2(const int32_t e) {
  // The first value this approximation fails for is 2^1651 which is just greater than 10^297.
  assert(e >= 0);
  assert(e <= 1650);
  return (((uint32_t)e) * 78913) >> 18;
}

// Returns floor(log_10(5^e)); requires 0 <= e <= 2620.
static inline uint32_t log10Pow5(const int32_t e) {
  // The first value this approximation fails for is 5^2621 which is just greater than 10^1832.
  assert(e >= 0);
  assert(e <= 2620);
  return (((uint32_t)e) * 732923) >> 20;
}

#if 0
void
Arcadia_Real32_toString
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value value,
    void* context,
    void (*function)(Arcadia_Thread*, void*, const Arcadia_Natural8Value*, Arcadia_SizeValue)
  )
{

  Arcadia_Natural32Value bits = Arcadia_Real32Value_getBits(thread, value);
  // (1) Extract the exponents bits, the significand bits, and the sign bits.
  Arcadia_Natural32Value ieeeExponentBits = (Arcadia_Real32Value_ExponentBitsMask & bits) >> Arcadia_Real32Value_ExponentBitsShift;
  Arcadia_Natural32Value ieeeSignificandBits = (Arcadia_Real32Value_SignificandBitsMask & bits) >> Arcadia_Real32Value_SignificandBitsShift;
  Arcadia_Natural32Value ieeeSignBits = (Arcadia_Real32Value_SignBitsMask & bits) >> Arcadia_Real32Value_SignBitsShift;
  // (2) Handle the cases of positive infinity, negative infinity, not a number.
  // If e = 11111111x2 = = ffx16 and f = 0 then we have positive infinite or negative infinity.
  // If e = 11111111x2 = = ffx16 and f != 0 then we have nan.
  // If e = 0 and f = 0 we have a signed zero.
  if (ieeeExponentBits == 0xff) {
    if (ieeeSignificandBits == 0) {
      (*function)(thread, context, ieeeSignBits ? positiveInfinityString : negativeInfinityString,
                                   ieeeSignBits ? sizeof(positiveInfinityString) - 1 : sizeof(negativeInfinityString) - 1);
      return;
    } else {
      (*function)(thread, context, ieeeSignBits ? positiveInfinityString : negativeInfinityString,
                                   ieeeSignBits ? sizeof(positiveInfinityString) - 1 : sizeof(negativeInfinityString) - 1);
      return;
    }
  } else if (ieeeExponentBits == 0x0 && ieeeSignificandBits == 0x0) {
    (*function)(thread, context, ieeeSignBits ? positiveZero : negativeZero,
                                 ieeeSignBits ? sizeof(positiveZero) - 1 : sizeof(negativeZero) - 1);
    return;
  }
  // (3) Compute m2 and e2.
  Arcadia_Natural32Value m2;
  Arcadia_Integer32Value e2;
  if (!ieeeExponentBits) {
    e2 = Arcadia_Integer32Value_Literal(1) - Arcadia_Real32Value_ExponentBias - 2;
    m2 = ieeeSignificandBits;
  } else {
    e2 = ((Arcadia_Integer32Value)ieeeExponentBits) - Arcadia_Real32Value_ExponentBias - 2;
    m2 = (1 << Arcadia_Real32Value_NumberOfExplicitSignificandBits) | ieeeSignificandBits;
  }
  const Arcadia_BooleanValue even = (m2 & 1) == 0;
  const Arcadia_BooleanValue acceptBounds = even;
}
#endif

#if 0
void
Arcadia_Real64_toString
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value value,
    void* context,
    void (*function)(Arcadia_Thread*, void*, const Arcadia_Natural8Value*, Arcadia_SizeValue)
  )
{
  Arcadia_Natural64Value bits = Arcadia_Real64Value_getBits(thread, value);
  // (1) Extract the exponents bits, the significand bits, and the sign bits.
  Arcadia_Natural64Value ieeeExponentBits = (Arcadia_Real64Value_ExponentBitsMask & bits) >> Arcadia_Real64Value_ExponentBitsShift;
  Arcadia_Natural64Value ieeeSignificandBits = (Arcadia_Real64Value_SignificandBitsMask & bits) >> Arcadia_Real64Value_SignificandBitsShift;
  Arcadia_Natural64Value ieeeSignBits = (Arcadia_Real64Value_SignBitsMask & bits) >> Arcadia_Real64Value_SignBitsShift;
  // (2) Handle the cases of positive infinity, negative infinity, not a number.
  // If e = 11111111111x2 = 7ffx16 and f = 0 then we have positive infinity or negative infinity
  // If e = 11111111111x2 = 7ffx16 and f != 0 then we have nan.
  // If e = 0 and f = 0 we have a signed zero.
  if (ieeeExponentBits == 0x7ff) {
    if (ieeeSignificandBits == 0) {
      (*function)(thread, context, ieeeSignBits ? positiveInfinityString : negativeInfinityString,
                                   ieeeSignBits ? sizeof(positiveInfinityString) - 1 : sizeof(negativeInfinityString) - 1);
      return;
    } else {
      (*function)(thread, context, ieeeSignBits ? positiveInfinityString : negativeInfinityString,
                                   ieeeSignBits ? sizeof(positiveInfinityString) - 1 : sizeof(negativeInfinityString) - 1);
      return;
    }
  } else if (ieeeExponentBits == 0x0 && ieeeSignificandBits == 0x0) {
    (*function)(thread, context, ieeeSignBits ? positiveZero : negativeZero,
                                 ieeeSignBits ? sizeof(positiveZero) - 1 : sizeof(negativeZero) - 1);
    return;
  }
  // (3) Compute m2 and e2.
  Arcadia_Natural64Value m2;
  Arcadia_Integer32Value e2;
  if (!ieeeExponentBits) {
    e2 = Arcadia_Integer32Value_Literal(1) - Arcadia_Real64Value_ExponentBias - 2;
    m2 = ieeeSignificandBits;
  } else {
    e2 = ((Arcadia_Integer32Value)ieeeExponentBits) - Arcadia_Real64Value_ExponentBias - 2;
    m2 = (1 << Arcadia_Real32Value_NumberOfExplicitSignificandBits) | ieeeSignificandBits;
  }
  const Arcadia_BooleanValue even = (m2 & 1) == 0;
  const Arcadia_BooleanValue acceptBounds = even;

  // (4) Compute mu, mv, and mw.
  // Implicit bool -> int conversion. True is 1, false is 0.
  const uint32_t mmShift = ieeeSignificandBits != 0 || ieeeExponentBits <= 1;

  const uint64_t mv = 4 * m2;
  const uint64_t mw = mv + 2;
  const uint64_t mz = mv - 1 - mmShift;

  uint64_t vr, vp, vm;
  int32_t e10;
  bool vmIsTrailingZeros = false;
  bool vrIsTrailingZeros = false;
}
#endif
