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

#if !defined(ARCADIA_RING1_BIGINTEGER_ADD_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_ADD_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"
#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

typedef struct Arcadia_BigInteger Arcadia_BigInteger;
typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

void
Arcadia_BigInteger_or3
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* result,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  );

// Compute the bitwise and of this BigInteger and another BigInteger and assign the sum to this BigInteger.
//
// Given two big integers a and b, their bitwise or is computed as follows:
// - Let l = min(n,m), h = max(n,m) where n is the number of limps in a and m be the number of limps in b.
// - The limps a_i and b_i, i in [0,l) are or'ed together such that the resulting big integer has limps c_i = a_i | b_i.
// - The limps a_i and b_i, i in [l,h) are set to a_i or b_i depending on wether a_i is longer or b_i is longer.
// - If l = 1 and c_0 = 0 then the resulting big integer is zero.
// - Otherwise the resulting big integer has limps c_l, ..., c_0, l > 0, c_i != 0.
//   Its sign is negative if a or b is negative and positive otherwise.
void
Arcadia_BigInteger_or
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  );

#endif // ARCADIA_RING1_BIGINTEGER_ADD_H_INCLUDED
