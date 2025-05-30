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

#if !defined(ARCADIA_RING2_IMPLEMENTATION_MAP_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_MAP_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Implementation/List.h"

Arcadia_declareObjectType(u8"Arcadia.Map", Arcadia_Map, u8"Arcadia.Object");

Arcadia_Map*
Arcadia_Map_create
  (
    Arcadia_Thread* thread
  );

Arcadia_Map*
Arcadia_Map_clone
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self
  );

void
Arcadia_Map_clear
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self
  );

Arcadia_SizeValue
Arcadia_Map_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Map const* self
  );

void
Arcadia_Map_set
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self,
    Arcadia_Value key,
    Arcadia_Value value
  );

Arcadia_Value
Arcadia_Map_get
  (
    Arcadia_Thread* thread,
    Arcadia_Map const* self,
    Arcadia_Value key
  );

Arcadia_List*
Arcadia_Map_getValues
  (
    Arcadia_Thread* thread,
    Arcadia_Map const* self
  );

Arcadia_List*
Arcadia_Map_getKeys
  (
    Arcadia_Thread* thread,
    Arcadia_Map const* self
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_MAP_H_INCLUDED
