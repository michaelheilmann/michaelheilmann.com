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

#include "R/Mil/Asts/LabelStatementAst.h"

#include "R/ArgumentsValidation.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(labelName:Arcadia.String)
/// @endcode
static void
Arcadia_Mil_LabelStatementAst_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_LabelStatementAst_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_LabelStatementAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_LabelStatementAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_LabelStatementAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_LabelStatementAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_LabelStatementAst_typeOperations = {
  .objectTypeOperations = &_Arcadia_Mil_LabelStatementAst_objectTypeOperations,
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

Rex_defineObjectType(u8"Arcadia.Mil.LabelStatementAst", Arcadia_Mil_LabelStatementAst, u8"Arcadia.Mil.StatementAst", Arcadia_Mil_StatementAst, &_Arcadia_Mil_LabelStatementAst_typeOperations);

static void
Arcadia_Mil_LabelStatementAst_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_LabelStatementAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_LabelStatementAst_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, &argumentValues[0]), _Arcadia_String_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  _self->labelName = Arcadia_Value_getObjectReferenceValue(&argumentValues[0]);
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_Mil_LabelStatementAst_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_LabelStatementAst* self
  )
{ Arcadia_Object_visit(process, self->labelName); }

Arcadia_Mil_LabelStatementAst*
Arcadia_Mil_LabelStatementAst_create
  (
    Arcadia_Process* process,
    Arcadia_String* labelName
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)labelName }, };
  Arcadia_Mil_LabelStatementAst* self = R_allocateObject(process, _Arcadia_Mil_LabelStatementAst_getType(process), 1, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
