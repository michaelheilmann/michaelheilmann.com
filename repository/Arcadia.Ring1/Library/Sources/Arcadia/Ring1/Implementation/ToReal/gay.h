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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TOREAL_GAY_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TOREAL_GAY_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/ToReal/result.h"
typedef struct Arcadia_BigInteger Arcadia_BigInteger;

/// David Gay's method.
/// @return #Arcadia_BooleanValue_True if that approach was successful for this input, #Arcadia_BooleanValue_False otherwise.
void
Arcadia_gayReal64
  (
    Arcadia_Thread* thread,
    Arcadia_ToReal64_Result* result,
    const Arcadia_Natural8Value* p,
    Arcadia_SizeValue n,
    const Approximation* a,
    Arcadia_NumberLiteral const* numberLiteral
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_TOREAL_GAY_H_INCLUDED
