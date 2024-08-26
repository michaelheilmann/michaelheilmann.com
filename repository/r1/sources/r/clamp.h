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

// Last modified: 2024-08-27

#if !defined(R_CLAMP_H_INCLUDED)
#define R_CLAMP_H_INCLUDED

#include "r/integer16.h"
#include "r/integer32.h"
#include "r/integer64.h"
#include "r/integer8.h"

#include "r/natural16.h"
#include "r/natural32.h"
#include "r/natural64.h"
#include "r/natural8.h"

#include "r/size.h"

#include "r/jumptarget.h"
#include "r/status.h"

#define Define(Type, Suffix) \
  static inline R_##Type##Value \
  R_clamp_##Suffix \
    ( \
      R_##Type##Value value, \
      R_##Type##Value lower, \
      R_##Type##Value upper  \
    ) \
  { \
    if (lower > upper) { \
      R_setStatus(R_Status_ArgumentValueInvalid); \
      R_jump(); \
    } \
    if (value < lower) value = lower; \
    else if (value > upper) value = upper; \
    return value; \
  }

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

#endif // R_CLAMP_H_INCLUDED
