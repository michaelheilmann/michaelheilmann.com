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

#include "Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/StatementsContext.h"

#include "Arcadia/Include.h"
#include "Arcadia/Mil/Frontend/Include.h"

static void
Arcadia_Mil_CallableContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_CallableContext_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_CallableContext* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_CallableContext_objectTypeOperations = {
  .construct = &Arcadia_Mil_CallableContext_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_CallableContext_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_CallableContext_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Mil_CallableContext_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Mil.CallableContext", Arcadia_Mil_CallableContext, u8"Arcadia.Object", Arcadia_Object, &_Arcadia_Mil_CallableContext_typeOperations);

static void
Arcadia_Mil_CallableContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_CallableContext* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_CallableContext_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->labels = Arcadia_Map_create(thread);
  _self->variables = Arcadia_List_create(thread);
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Mil_CallableContext_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_CallableContext* self
  )
{
  if (self->labels) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->labels);
  }
  if (self->variables) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->variables);
  }
}

Arcadia_Mil_CallableContext*
Arcadia_Mil_CallableContext_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Mil_CallableContext* self = Arcadia_allocateObject(thread, _Arcadia_Mil_CallableContext_getType(thread), 0, &argumentValues[0]);
  return self;
}

void
Arcadia_Mil_CallableContext_onReset
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_CallableContext* self
  )
{
  Arcadia_Collection_clear(thread, (Arcadia_Collection*)self->labels);
  Arcadia_Collection_clear(thread, (Arcadia_Collection*)self->variables);
  self->statementIndex = 0;
}

void
Arcadia_Mil_CallableContext_onDefineLabel
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_CallableContext* self,
    Arcadia_String* name,
    Arcadia_Mil_LabelStatementAst* ast,
    Arcadia_Natural32Value instructionIndex
  )
{
  Arcadia_Value k;
  Arcadia_Value_setObjectReferenceValue(&k, name);
  Arcadia_Value v = Arcadia_Map_get(thread, self->labels, k);
  if (!Arcadia_Value_isVoidValue(&v)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Value_setObjectReferenceValue(&v, ast);
  Arcadia_Map_set(thread, self->labels, k, v, NULL, NULL);
}

void
Arcadia_Mil_CallableContext_onParameterVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_CallableContext* self,
    Arcadia_String* name,
    Arcadia_Mil_Ast* ast
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->variables); i < n; ++i) {
    Arcadia_Value args[2] = {
      Arcadia_Value_makeObjectReferenceValue(name),
      Arcadia_List_getAt(thread, self->variables, i),
    };
    if (Arcadia_Value_isEqualTo(thread, &args[0], &args[1])) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
  }
}

void
Arcadia_Mil_CallableContext_onLocalVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_CallableContext* context,
    Arcadia_String* name,
    Arcadia_Mil_VariableDefinitionStatementAst* ast
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)context->variables); i < n; ++i) {
    Arcadia_Value args[2] = {
      Arcadia_Value_makeObjectReferenceValue(name),
      Arcadia_List_getAt(thread, context->variables, i),
    };
    if (Arcadia_Value_isEqualTo(thread, &args[0], &args[1])) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
  }
}
