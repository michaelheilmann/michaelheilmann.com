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

#include "Arcadia/Visuals/Commands/EmitCommand.h"

static void
Arcadia_Visuals_EmitCommand_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_EmitCommand* self
  );

static void
Arcadia_Visuals_EmitCommand_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_EmitCommand* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_Visuals_EmitCommand_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Visuals_EmitCommand_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.EmitCommand", Arcadia_Visuals_EmitCommand,
                         u8"Arcadia.Visuals.Command", Arcadia_Visuals_Command,
                         &_typeOperations);

static void
Arcadia_Visuals_EmitCommand_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_EmitCommand* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_EmitCommand_getType(thread);
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural64Value(thread, Arcadia_ValueStack_getNatural64Value(thread, 2));
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  self->message = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_Visuals_EmitCommand_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_EmitCommand* self
  )
{
  if (self->message) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->message);
  }
}
