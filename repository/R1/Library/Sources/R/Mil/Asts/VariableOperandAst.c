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

#include "R/Mil/Asts/VariableOperandAst.h"

#include "R/ArgumentsValidation.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(value : Arcadia.Library.String)
/// @endcode
static void
Arcadia_Mil_VariableOperandAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_VariableOperandAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_VariableOperandAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_VariableOperandAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_VariableOperandAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_VariableOperandAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_VariableOperandAst_typeOperations = {
  .objectTypeOperations = &_Arcadia_Mil_VariableOperandAst_objectTypeOperations,
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

Rex_defineObjectType(u8"Arcadia.Mil.VariableOperandAst", Arcadia_Mil_VariableOperandAst, u8"Arcadia.Mil.OperandAst", Arcadia_Mil_OperandAst, &_Arcadia_Mil_VariableOperandAst_typeOperations);

void
Arcadia_Mil_VariableOperandAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_VariableOperandAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_VariableOperandAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void }, };
    Rex_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
   if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->value = (Arcadia_String*)R_Argument_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, _self, _type);
}

static void
Arcadia_Mil_VariableOperandAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_VariableOperandAst* self
  )
{ Arcadia_Object_visit(thread, self->value); }

Arcadia_Mil_VariableOperandAst*
Arcadia_Mil_VariableOperandAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* value
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)value } };
  Arcadia_Mil_VariableOperandAst* self = Arcadia_allocateObject(thread, _Arcadia_Mil_VariableOperandAst_getType(thread), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
