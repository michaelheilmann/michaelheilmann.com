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

// Last modified: 2024-09-01

#if !defined(ARCADIA_RING1_UTF8_H_INCLUDED)
#define ARCADIA_RING1_UTF8_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"

#define Arcadia_Utf8CodePoint_Last (0x0010ffff)
Arcadia_StaticAssert(Arcadia_Utf8CodePoint_Last <= Arcadia_Natural32Value_Maximum - 3, "<internal error>");

// https://michaelheilmann.com/repository/Arcadia.Ring1/#Arcadia-isUtf8
Arcadia_BooleanValue
Arcadia_isUtf8
  (
    Arcadia_Process* process,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes,
    Arcadia_SizeValue* numberOfSymbols
  );

#endif // ARCADIA_RING1_UTF8_H_INCLUDED
