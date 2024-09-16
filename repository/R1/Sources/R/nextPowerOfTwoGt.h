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

// Last modified: 2024-09-15

#if !defined(R_NEXTPOWEROFTWOGT_H_INCLUDED)
#define R_NEXTPOWEROFTWOGT_H_INCLUDED

#include "R/Integer16.h"
#include "R/Integer32.h"
#include "R/Integer64.h"
#include "R/Integer8.h"

#include "R/Natural16.h"
#include "R/Natural32.h"
#include "R/Natural64.h"
#include "R/Natural8.h"

#include "R/Size.h"

#define Define(Type, Suffix) \
  R_##Type##Value \
  R_nextPowerOfTwoGt_##Suffix \
    ( \
      R_##Type##Value x \
    ); 

Define(Integer16, i16)
Define(Integer32, i32)
Define(Integer64, i64)
Define(Integer8, i8)

Define(Natural16, n16)
Define(Natural32, n32)
Define(Natural64, n64)
Define(Natural8, n8)

Define(Size, s)

#undef Define

#endif // R_NEXTPOWEROFTWOGT_H_INCLUDED
