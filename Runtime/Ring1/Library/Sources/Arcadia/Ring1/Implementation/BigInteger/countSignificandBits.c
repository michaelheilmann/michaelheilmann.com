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
#include "Arcadia/Ring1/Implementation/BigInteger/countSignificandBits.h"

#include "Arcadia/Ring1/Include.h"

Arcadia_SizeValue
Arcadia_BigInteger_countSignificandBits
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{
  if (Arcadia_BigInteger_isZero(thread, self)) {
    return Arcadia_SizeValue_Literal(0);
  }
  return Arcadia_BigInteger_BitsPerLimp * (self->numberOfLimps - 1) + Arcadia_countSignificandBitsNatural32Value(thread, self->limps[self->numberOfLimps - 1]);
}
