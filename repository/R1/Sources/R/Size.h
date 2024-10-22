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

// Last modified: 2024-10-27

#if !defined(R_SIZEVALUE_H_INCLUDED)
#define R_SIZEVALUE_H_INCLUDED

#include <stddef.h>
typedef void R_Type;

typedef size_t R_SizeValue;

#define R_SizeValue_Minimum ((size_t)0)

#define R_SizeValue_Maximum (SIZE_MAX)

#define R_SizeValue_NumberOfBytes (sizeof(size_t))
static_assert(R_SizeValue_NumberOfBytes == 4 || R_SizeValue_NumberOfBytes == 8, "R.SizeValue.NumberOfBytes must be one of 4 or 8");

#define R_SizeValue_NumberOfBits (R_SizeValue_NumberOfBytes * 8)

#define R_SizeValue_Literal(x) ((size_t)x)

R_Type*
_R_SizeValue_getType
  (
  );

#endif // R_SIZEVALUE_H_INCLUDED
