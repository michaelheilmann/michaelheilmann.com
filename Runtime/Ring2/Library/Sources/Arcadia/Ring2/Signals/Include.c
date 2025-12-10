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
#include "Arcadia/Ring2/Signals/Include.h"

#include "Arcadia/Ring2/Collections/ArrayList.h"
#include "Arcadia/Ring2/Signals/Node.h"

static void
Arcadia_Signal_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self
  );

static void
Arcadia_Signal_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_SignalDispatch* self
  );

static void
Arcadia_Signal_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self
  );

static void
Arcadia_Signal_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Signal_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Signal_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Signal_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Signal", Arcadia_Signal,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Signal_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Signal_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  self->subscriptions = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Signal_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_SignalDispatch* self
  )
{ }

static void
Arcadia_Signal_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Signal_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self
  )
{
  if (self->subscriptions) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->subscriptions);
  }
}

Arcadia_Signal*
Arcadia_Signal_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Signal);
}

void
Arcadia_Signal_subscribe
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self,
    Arcadia_Value subscriber,
    Arcadia_Value procedure
  )
{
  if (Arcadia_Value_isForeignProcedureValue(&procedure)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Signal_Node* node = Arcadia_Signal_Node_create(thread, subscriber, procedure);
  Arcadia_List_insertBackObjectReferenceValue(thread, self->subscriptions, (Arcadia_Object*)node);
}

void
Arcadia_Signal_unsubscribe
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self,
    Arcadia_Value subscriber,
    Arcadia_Value procedure
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->subscriptions); i < n;) {
    Arcadia_Signal_Node* element = (Arcadia_Signal_Node*)Arcadia_List_getObjectReferenceValueAt(thread, self->subscriptions, i);
    if (Arcadia_Value_isEqualTo(thread, &subscriber, &element->subscriber) && Arcadia_Value_isEqualTo(thread, &procedure, &element->procedure)) {
      if (self->reentrancy) {
        element->dead = Arcadia_BooleanValue_True;
      } else {
        Arcadia_List_removeAt(thread, self->subscriptions, i, 1);
        n--;
      }
    } else {
      i++;
    }
  }
}

void
Arcadia_Signal_notify
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self,
    Arcadia_Value argument
  )
{
  if (self->reentrancy == Arcadia_Natural32Value_Maximum) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->reentrancy++;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->subscriptions); i < n; ++i) {
      Arcadia_Signal_Node* element = (Arcadia_Signal_Node*)Arcadia_List_getObjectReferenceValueAt(thread, self->subscriptions, i);
      if (!element->dead) {
        Arcadia_ValueStack_pushValue(thread, &element->subscriber);
        Arcadia_ValueStack_pushValue(thread, &argument);
        Arcadia_ValueStack_pushNatural8Value(thread, 2);
        Arcadia_ForeignProcedureValue p = Arcadia_Value_getForeignProcedureValue(&element->procedure);
        (*p)(thread);
      }
    }
    Arcadia_Thread_popJumpTarget(thread);
    self->reentrancy--;
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    self->reentrancy--;
    Arcadia_Thread_jump(thread);
  }
}
