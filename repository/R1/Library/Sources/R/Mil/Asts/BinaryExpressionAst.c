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

#include "R/Mil/Asts/BinaryExpressionAst.h"

#include "R/ArgumentsValidation.h"
#include "R/Mil/Ast.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(type : Arcadia.Mil.BinaryExpressionAstType, operand1 : Arcadia.Mil.OperandAst, operand2 : Arcadia.Mil.OperandAst)
/// @endcode
static void
Arcadia_Mil_BinaryExpressionAst_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_BinaryExpressionAst_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_BinaryExpressionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_BinaryExpressionAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_BinaryExpressionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_BinaryExpressionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_BinaryExpressionAst_typeOperations = {
  .objectTypeOperations = &_Arcadia_Mil_BinaryExpressionAst_objectTypeOperations,
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

Rex_defineObjectType(u8"Arcadia.Mil.BinaryExpressionAst", Arcadia_Mil_BinaryExpressionAst, u8"Arcadia.Mil.ExpressionAst", Arcadia_Mil_ExpressionAst, &_Arcadia_Mil_BinaryExpressionAst_typeOperations);

static void
Arcadia_Mil_BinaryExpressionAst_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_BinaryExpressionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_BinaryExpressionAst_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }

  if (3 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }

  if (!Arcadia_Value_isInteger32Value(&argumentValues[0])) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }

  if (!Arcadia_Value_isObjectReferenceValue(&argumentValues[1])) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, &argumentValues[1]), _Arcadia_Mil_OperandAst_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }

  if (!Arcadia_Value_isObjectReferenceValue(&argumentValues[2])) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, &argumentValues[2]), _Arcadia_Mil_OperandAst_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }

  _self->type = Arcadia_Value_getInteger32Value(&argumentValues[0]);
  _self->operand1 = Arcadia_Value_getObjectReferenceValue(&argumentValues[1]);
  _self->operand2 = Arcadia_Value_getObjectReferenceValue(&argumentValues[2]);

  Arcadia_Object_setType(process, _self, _type);  
}

static void
Arcadia_Mil_BinaryExpressionAst_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_BinaryExpressionAst* self
  )
{
  Arcadia_Object_visit(process, self->operand1);
  Arcadia_Object_visit(process, self->operand2);
}

Arcadia_Mil_BinaryExpressionAst*
Arcadia_Mil_BinaryExpressionAst_create
  (
    Arcadia_Process* process,
    Arcadia_Mil_BinaryExpressionAstType type,
    Arcadia_Mil_OperandAst* operand1,
    Arcadia_Mil_OperandAst* operand2
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Integer32, .integer32Value = type },
                               {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)operand1 },
                               {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)operand2 }, };
  Arcadia_Mil_BinaryExpressionAst* self = R_allocateObject(process, _Arcadia_Mil_BinaryExpressionAst_getType(process), 3, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
