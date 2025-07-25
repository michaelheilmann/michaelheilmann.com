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

#if !defined(ARCADIA_RING2_IMPLEMENTATION_COLLECTION_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_COLLECTION_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
#error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Collection", Arcadia_Collection, u8"Arcadia.Object");

struct Arcadia_Collection {
  Arcadia_Object _parent;
  void (*clear)(Arcadia_Thread*, Arcadia_Collection*);
  Arcadia_SizeValue (*getSize)(Arcadia_Thread*, Arcadia_Collection*);
  Arcadia_BooleanValue (*isEmpty)(Arcadia_Thread*, Arcadia_Collection*);
};

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_Collection_clear
void
Arcadia_Collection_clear
  (
    Arcadia_Thread* thread,
    Arcadia_Collection* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_Colleciton_getSize
Arcadia_SizeValue
Arcadia_Collection_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Collection* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_Collection_isEmpty
Arcadia_BooleanValue
Arcadia_Collection_isEmpty
  (
    Arcadia_Thread* thread,
    Arcadia_Collection* self
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_COLLECTION_H_INCLUDED
