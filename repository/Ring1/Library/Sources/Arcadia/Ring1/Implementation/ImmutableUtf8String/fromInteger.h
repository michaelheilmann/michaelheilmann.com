// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEUTF8STRING_FROMINTEGER_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEUTF8STRING_FROMINTEGER_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"
typedef struct Arcadia_ImmutableUtf8String Arcadia_ImmutableUtf8String;

Arcadia_ImmutableUtf8String*
_createFromInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value integer16Value
  );

Arcadia_ImmutableUtf8String*
_createFromInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value
  );

Arcadia_ImmutableUtf8String*
_createFromInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value integer64Value
  );

Arcadia_ImmutableUtf8String*
_createFromInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value integer8Value
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_IMMUTABLEUTF8STRING_FROMINTEGER_H_INCLUDED
