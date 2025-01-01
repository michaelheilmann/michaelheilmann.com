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

// Last modified: 2024-10-27

#if !defined(R_INTEGER64VALUE_H_INCLUDED)
#define R_INTEGER64VALUE_H_INCLUDED

#include "R/Scalar.h"
#include "Arcadia/Ring1/Implementation/Process.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <stdint.h>

typedef int64_t Arcadia_Integer64Value;

#define Arcadia_Integer64Value_Minimum (INT64_MIN)

#define Arcadia_Integer64Value_Maximum (INT64_MAX)

#define Arcadia_Integer64Value_NumberOfBytes (sizeof(int64_t))
Arcadia_StaticAssert(Arcadia_Integer64Value_NumberOfBytes == 8, "Arcadia.Integer64Value.NumberOfByes must be 8");

#define Arcadia_Integer64Value_NumberOfBits (Arcadia_Integer64Value_NumberOfBytes * 8)

#define Arcadia_Integer64Value_Literal(x) INT64_C(x)

Rex_declareScalarType(Arcadia_Integer64);

#endif // R_INTEGER64VALUE_H_INCLUDED