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
#include "Arcadia/Ring1/Implementation/BigInteger/and.h"

#include "Arcadia/Ring1/Include.h"
#include <assert.h>

void
Arcadia_BigInteger_and
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  )
{
  if (self == other) {
    return;  
  } else if (Arcadia_BigInteger_isZero(thread, self) || Arcadia_BigInteger_isZero(thread, other)) {
    Arcadia_BigInteger_setZero(thread, self);
  } else {
    Arcadia_SizeValue k = Arcadia_minimumSizeValue(thread, self->numberOfLimps, other->numberOfLimps);
    self->numberOfLimps = k;
    for (Arcadia_SizeValue i = 0; i < k; ++i) {
      self->limps[i] &= other->limps[i];
    }
    while (self->numberOfLimps > 1 && self->limps[self->numberOfLimps - 1] == 0) {
      self->numberOfLimps--;
    }
    if (self->sign != other->sign) {
      self->sign = +1;
    }
    if (self->limps[0] == 0) {
      self->sign = 0;
    }
  }
}
