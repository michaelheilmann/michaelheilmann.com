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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_VOID_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_VOID_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/_declareScalarType.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <stdint.h>

typedef uint8_t Arcadia_VoidValue;

#define Arcadia_VoidValue_Void (UINT8_C(0))

#define Arcadia_VoidValue_NumberOfBytes (sizeof(uint8_t))

#define Arcadia_VoidValue_NumberOfBits (Arcadia_VoidValue_NumberOfBytes * 8)

Arcadia_declareScalarType(Arcadia_Void);

#endif // ARCADIA_RING1_IMPLEMENTATION_VOID_H_INCLUDED
