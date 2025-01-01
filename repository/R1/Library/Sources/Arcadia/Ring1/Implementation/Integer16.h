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

// Last modified: 2024-10-25

#if !defined(ARCADIA_RING1_IMPLEMENTATION_INTEGER16_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_INTEGER16_H_INCLUDED

#include "R/Scalar.h"
#include "Arcadia/Ring1/Implementation/Process.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <stdint.h>

typedef int16_t Arcadia_Integer16Value;

#define Arcadia_Integer16Value_Minimum (INT16_MIN)

#define Arcadia_Integer16Value_Maximum (INT16_MAX)

#define Arcadia_Integer16Value_NumberOfBytes (sizeof(int16_t))
Arcadia_StaticAssert(Arcadia_Integer16Value_NumberOfBytes == 2, "Arcadia.Integer16Value.NumberOfBytes must be 2");

#define Arcadia_Integer16Value_NumberOfBits (Arcadia_Integer16Value_NumberOfBytes * 8)

#define Arcadia_Integer16Value_Literal(x) INT16_C(x)

Rex_declareScalarType(Arcadia_Integer16);

#endif // ARCADIA_RING1_IMPLEMENTATION_INTEGER16_H_INCLUDED
