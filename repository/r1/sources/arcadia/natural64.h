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

#if !defined(ARCADIA_NATURAL64VALUE_H_INCLUDED)
#define ARCADIA_NATURAL64VALUE_H_INCLUDED

#include <inttypes.h>

typedef uint64_t R_Natural64Value;

#define R_Natural64Value_Minimum (UINT64_C(0))

#define R_Natural64Value_Maximum (UINT64_MAX)

#define R_Natural64Value_NumberOfBytes (sizeof(uint64_t))

static_assert(R_Natural64Value_NumberOfBytes == 8, "R.Natural64Value.NumberOfBytes must be 8");

#define R_Natural64Value_NumberOfBits (R_Natural64Value_NumberOfBytes * 8)

#endif // ARCADIA_NATURAL64_H_INCLUDED
