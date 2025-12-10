// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_SIGNALS_NODE_H_INCLUDED)
#define ARCADIA_SIGNALS_NODE_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/Collections/List.h"

Arcadia_declareObjectType(u8"Arcadia.Signal.Node", Arcadia_Signal_Node,
                          u8"Arcadia.Object");

struct Arcadia_Signal_NodeDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_Signal_Node {
  Arcadia_Object _parent;
  // If this node is dead.
  Arcadia_BooleanValue dead;
  // The subscriber in this node.
  Arcadia_Value subscriber;
  // The procedure in this node.
  Arcadia_Value procedure;
};

Arcadia_Signal_Node*
Arcadia_Signal_Node_create
  (
    Arcadia_Thread* thread,
    Arcadia_Value subscriber,
    Arcadia_Value procedure
  );

#endif // ARCADIA_SIGNALS_NODE_H_INCLUDED
