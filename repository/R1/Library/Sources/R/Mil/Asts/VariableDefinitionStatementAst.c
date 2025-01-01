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

#include "R/Mil/Asts/VariableDefinitionStatementAst.h"

#include "R/ArgumentsValidation.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(name:R.String)
/// @endcode
static void
R_Mil_VariableDefinitionStatementAst_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_Mil_VariableDefinitionStatementAst_visit
  (
    Arcadia_Process* process,
    R_Mil_VariableDefinitionStatementAst* self
  );

static const R_ObjectType_Operations _R_Mil_VariableDefinitionStatementAst_objectTypeOperations = {
  .construct = &R_Mil_VariableDefinitionStatementAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_VariableDefinitionStatementAst_visit,
};

static const Arcadia_Type_Operations _R_Mil_VariableDefinitionStatementAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_VariableDefinitionStatementAst_objectTypeOperations,
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

Rex_defineObjectType(u8"R.Mil.VariableDefinitionStatementAst", R_Mil_VariableDefinitionStatementAst, u8"R.Mil.StatementAst", R_Mil_StatementAst, &_R_Mil_VariableDefinitionStatementAst_typeOperations);

static void
R_Mil_VariableDefinitionStatementAst_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Mil_VariableDefinitionStatementAst* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Mil_VariableDefinitionStatementAst_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->name = R_Argument_getObjectReferenceValue(process, &argumentValues[0], _R_String_getType(process));
  R_Object_setType(_self, _type);
}

static void
R_Mil_VariableDefinitionStatementAst_visit
  (
    Arcadia_Process* process,
    R_Mil_VariableDefinitionStatementAst* self
  )
{ R_Object_visit(self->name); }

R_Mil_VariableDefinitionStatementAst*
R_Mil_VariableDefinitionStatementAst_create
  (
    Arcadia_Process* process,
    R_String* name
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = name }, };
  R_Mil_VariableDefinitionStatementAst* self = R_allocateObject(process, _R_Mil_VariableDefinitionStatementAst_getType(process), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/