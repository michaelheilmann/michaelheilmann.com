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

#if !defined(ARCADIA_SIGNALS_INCLUDE_H_INCLUDED)
#define ARCADIA_SIGNALS_INCLUDE_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/Collections/List.h"

Arcadia_declareObjectType(u8"Arcadia.Signal", Arcadia_Signal,
                          u8"Arcadia.Object");

struct Arcadia_SignalDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_Signal {
  Arcadia_Object _parent;
  Arcadia_Natural32Value reentrancy;
  Arcadia_List* subscriptions;
};

Arcadia_Signal*
Arcadia_Signal_create
  (
    Arcadia_Thread* thread
  );

// The procedure must be of type Arcadia.ForeignProcedure,
// It receives as its first argument the subsriber and the argument of the invocation as its second argument.
void
Arcadia_Signal_subscribe
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self,
    Arcadia_Value subscriber,
    Arcadia_Value procedure
  );

void
Arcadia_Signal_unsubscribe
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self,
    Arcadia_Value subscriber,
    Arcadia_Value procedure
  );

// Expects the arguments on the stack followed by the number of arguments.
void
Arcadia_Signal_notify
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self,
    Arcadia_Value argument
  );

#endif // ARCADIA_SIGNALS_INCLUDE_H_INCLUDED
