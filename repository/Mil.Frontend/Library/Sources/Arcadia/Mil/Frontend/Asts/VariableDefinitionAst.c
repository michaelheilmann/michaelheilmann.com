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

#include "Arcadia/Mil/Frontend/Asts/VariableDefinitionAst.h"

#include "Arcadia/Mil/Frontend/Include.h"

/// @code
/// construct(variableName:Arcadia.String)
/// @endcode
static void
Arcadia_Mil_VariableDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_VariableDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_VariableDefinitionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_VariableDefinitionAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_VariableDefinitionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_VariableDefinitionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_VariableDefinitionAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Mil_VariableDefinitionAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Mil.VariableDefinitionAst", Arcadia_Mil_VariableDefinitionAst, u8"Arcadia.Mil.Ast", Arcadia_Mil_Ast, &_Arcadia_Mil_VariableDefinitionAst_typeOperations);

static void
Arcadia_Mil_VariableDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_VariableDefinitionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_VariableDefinitionAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = { Arcadia_Value_Initializer() };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->variableName = (Arcadia_String*)Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Mil_VariableDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_VariableDefinitionAst* self
  )
{ Arcadia_Object_visit(thread, (Arcadia_Object*)self->variableName); }

Arcadia_Mil_VariableDefinitionAst*
Arcadia_Mil_VariableDefinitionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* variableName
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeObjectReferenceValue(variableName),
  };
  Arcadia_Mil_VariableDefinitionAst* self = Arcadia_allocateObject(thread, _Arcadia_Mil_VariableDefinitionAst_getType(thread), 1, &argumentValues[0]);
  return self;
}
