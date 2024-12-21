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

// Last modified: 2024-09-26

#if !defined(R_CONVERT_STRINGTOREAL_H_INCLUDED)
#define R_CONVERT_STRINGTOREAL_H_INCLUDED

#include "R/Real32.h"
#include "R/Real64.h"
#include "R/Size.h"

R_Real32Value
R_toReal32
  (
    char const* p,
    R_SizeValue n
  );

R_Real64Value
R_toReal64
  (
    char const* p,
    R_SizeValue n
  );

#endif // R_CONVERT_STRINGTOREAL_H_INCLUDED