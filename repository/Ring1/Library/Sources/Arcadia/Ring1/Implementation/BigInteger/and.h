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
Arcadia_BigInteger_and3
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* result,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  );

// Compute the bitwise and of this big integer and another big integer.
//
// Given two big integers a and b, their bitwise and is computed as follows:
// - Let k = min(n,m) where n is the number of limps in this big integer and m be the number of limps in the other big integer.
// - The number of limps of c is k.
// - The limps a_i and b_i, i in [0,k) are and'ed together such that the resulting big integer has limps c_i = a_i & b_i.
// - Next, the limps c_k, c_[k-1], ... c_1 are removed if they are zero. There remain l <= k limps.
// - If l = 1 and c_0 = 0 then the resulting big integer is zero.
// - Otherwise the resulting big integer has limps c_l, ..., c_0, l > 1 and c_i != 0 i in [0,l).
//   Its sign is negative if both and b are negative and positive otherwise.
void
Arcadia_BigInteger_and
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  );

#endif // ARCADIA_RING1_BIGINTEGER_ADD_H_INCLUDED
