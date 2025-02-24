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

// Last modified: 2025-01-01

#if !defined(ARCADIA_RING1_SUPPORT_STRINGTOFLOAT_H_INCLUDED)
#define ARCADIA_RING1_SUPPORT_STRINGTOFLOAT_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <float.h>
#include "Arcadia/Ring1/Support/apint10.h"
#include "Arcadia/Ring1/Support/apreal10.h"
#include "Arcadia/Ring1/Support/ieee754.h"

/// @return @a 0 on success. A non-zero value on failure.
int
utf8_to_flt
  (
    const uint8_t* p,
    size_t n,
    float* v
  );
  
/// @return @a 0 on success. A non-zero value on failure.
int
utf8_to_dbl
  (
    const uint8_t* p,
    size_t n,
    double* v
  );

#endif // ARCADIA_RING1_SUPPORT_STRINGTOFLOAT_H_INCLUDED
