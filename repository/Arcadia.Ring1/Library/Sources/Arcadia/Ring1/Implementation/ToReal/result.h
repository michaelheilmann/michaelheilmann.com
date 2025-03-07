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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TOREAL_RESULT_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TOREAL_RESULT_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Real64.h"
#include "Arcadia/Ring1/Implementation/BigInteger/Include.h"
#include "Arcadia/Ring1/Implementation/NumberLiteral.h"

typedef struct Arcadia_ToReal64_Result {
  
  /// The significand bits.
  Arcadia_Natural64Value significand;
  
  /// The exponent bits.
  Arcadia_Integer32Value exponent;
  
  /// Wether the number is positive or negative.
  Arcadia_BooleanValue negative;
  
} Arcadia_ToReal64_Result;

typedef struct State {
  Arcadia_NumberLiteral literal;
  Arcadia_BigInteger* significand;
  Arcadia_BigInteger* exponent;
  Arcadia_BooleanValue negative;
} State;

void
Arcadia_ToReal64_BitsToValue
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value* target,
    Arcadia_ToReal64_Result* source
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_TOREAL_RESULT_H_INCLUDED
