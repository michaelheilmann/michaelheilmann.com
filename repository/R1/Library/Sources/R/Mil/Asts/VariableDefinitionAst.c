// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2025-01-01

#include "R/Mil/Asts/VariableDefinitionAst.h"

#include "R/ArgumentsValidation.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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
  .objectTypeOperations = &_Arcadia_Mil_VariableDefinitionAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType(u8"Arcadia.Mil.VariableDefinitionAst", Arcadia_Mil_VariableDefinitionAst, u8"Arcadia.Mil.ClassMemberDefinitionAst", Arcadia_Mil_ClassMemberDefinitionAst, &_Arcadia_Mil_VariableDefinitionAst_typeOperations);

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
    Rex_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->variableName = (Arcadia_String*)R_Argument_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, _self, _type);
}

static void
Arcadia_Mil_VariableDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_VariableDefinitionAst* self
  )
{ Arcadia_Object_visit(thread, self->variableName); }

Arcadia_Mil_VariableDefinitionAst*
Arcadia_Mil_VariableDefinitionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* variableName
  )
{
  Arcadia_Value argumentValues[] = {
    {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)variableName },
  };
  Arcadia_Mil_VariableDefinitionAst* self = Arcadia_allocateObject(thread, _Arcadia_Mil_VariableDefinitionAst_getType(thread), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
