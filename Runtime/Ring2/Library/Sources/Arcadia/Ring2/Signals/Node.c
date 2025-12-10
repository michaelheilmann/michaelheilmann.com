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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Signals/Node.h"

#include "Arcadia/Ring2/Collections/ArrayList.h"

static void
Arcadia_Signal_Node_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal_Node* self
  );

static void
Arcadia_Signal_Node_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal_NodeDispatch* self
  );

static void
Arcadia_Signal_Node_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal_Node* self
  );

static void
Arcadia_Signal_Node_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal_Node* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Signal_Node_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Signal_Node_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Signal_Node_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Signal.Node", Arcadia_Signal_Node,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Signal_Node_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal_Node* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Signal_Node_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal_Node* self
  )
{
  Arcadia_Value_visit(thread, &self->subscriber);
  Arcadia_Value_visit(thread, &self->procedure);
}

static void
Arcadia_Signal_Node_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal_Node* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Signal_Node_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  self->dead = Arcadia_BooleanValue_False;
  self->subscriber = Arcadia_ValueStack_getValue(thread, 2);
  self->procedure = Arcadia_ValueStack_getValue(thread, 1);
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Signal_Node_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal_NodeDispatch* self
  )
{ }

Arcadia_Signal_Node*
Arcadia_Signal_Node_create
  (
    Arcadia_Thread* thread,
    Arcadia_Value subscriber,
    Arcadia_Value procedure
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushValue(thread, &subscriber);
  Arcadia_ValueStack_pushValue(thread, &procedure);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_Signal_Node);
}
