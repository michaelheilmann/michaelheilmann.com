// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-08-25

#if !defined(ARCADIA_INTEGER16VALUE_H_INCLUDED)
#define ARCADIA_INTEGER16VALUE_H_INCLUDED

#include <inttypes.h>

typedef int16_t R_Integer16Value;

#define R_Integer16Value_Minimum (INT16_MIN)

#define R_Integer16Value_Maximum (INT16_MAX)

#define R_Integer16Value_NumberOfBytes (sizeof(int16_t))

static_assert(R_Integer16Value_NumberOfBytes == 2, "R.Integer16Value.NumberOfBytes must be 2");

#define R_Integer16Value_NumberOfBits (R_Integer16Value_NumberOfBytes * 8)

#endif // ARCADIA_INTEGER16VALUE_H_INCLUDED
