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

#include "R/Mil/Asts/LoadExpressionAst.h"

#include "R/ArgumentsValidation.h"
#include "R/Mil/Asts/OperandAst.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(expression : R.Mil.OperandAst)
/// @endcode
static void
R_Mil_LoadExpressionAst_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_Mil_LoadExpressionAst_visit
  (
    Arcadia_Process* process,
    R_Mil_LoadExpressionAst* self
  );

static const Arcadia_ObjectType_Operations _R_Mil_LoadExpressionAst_objectTypeOperations = {
  .construct = &R_Mil_LoadExpressionAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_LoadExpressionAst_visit,
};

static const Arcadia_Type_Operations _R_Mil_LoadExpressionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_LoadExpressionAst_objectTypeOperations,
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

Rex_defineObjectType(u8"R.Mil.LoadExpressionAst", R_Mil_LoadExpressionAst, u8"R.Mil.ExpressionAst", R_Mil_ExpressionAst, &_R_Mil_LoadExpressionAst_typeOperations);

static void
R_Mil_LoadExpressionAst_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Mil_LoadExpressionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Mil_LoadExpressionAst_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }

  if (1 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }

  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, &argumentValues[0]), _R_Mil_OperandAst_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }

  _self->operand = Arcadia_Value_getObjectReferenceValue(&argumentValues[0]);

  Arcadia_Object_setType(process, _self, _type);
}

static void
R_Mil_LoadExpressionAst_visit
  (
    Arcadia_Process* process,
    R_Mil_LoadExpressionAst* self
  )
{
  Arcadia_Object_visit(process, self->operand);
}

R_Mil_LoadExpressionAst*
R_Mil_LoadExpressionAst_create
  (
    Arcadia_Process* process,
    R_Mil_OperandAst* operand
  )
{ 
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)operand } };
  R_Mil_LoadExpressionAst* self = R_allocateObject(process, _R_Mil_LoadExpressionAst_getType(process), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
