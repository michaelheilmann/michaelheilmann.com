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

#include "R/Mil/Asts/ProcedureDefinitionAst.h"

#include "R/ArgumentsValidation.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(nativeName:Arcadia.String, procedureName:Arcadia.String,procedureParameters:R.List,procedureBody:List)
/// @endcode
static void
R_Mil_ProcedureDefinitionAst_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_Mil_ProcedureDefinitionAst_visit
  (
    Arcadia_Process* process,
    R_Mil_ProcedureDefinitionAst* self
  );

static const Arcadia_ObjectType_Operations _R_Mil_ProcedureDefinitionAst_objectTypeOperations = {
  .construct = &R_Mil_ProcedureDefinitionAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_ProcedureDefinitionAst_visit,
};

static const Arcadia_Type_Operations _R_Mil_ProcedureDefinitionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ProcedureDefinitionAst_objectTypeOperations,
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

Rex_defineObjectType(u8"R.Mil.ProcedureDefinitionAst", R_Mil_ProcedureDefinitionAst, u8"R.Mil.DefinitionAst", R_Mil_DefinitionAst, &_R_Mil_ProcedureDefinitionAst_typeOperations);

static void
R_Mil_ProcedureDefinitionAst_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Mil_ProcedureDefinitionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Mil_ProcedureDefinitionAst_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }

  if (5 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->entry = Arcadia_Value_getBooleanValue(&argumentValues[0]);
  _self->nativeName = R_Argument_getObjectReferenceValueOrNull(process, &argumentValues[1], _Arcadia_String_getType(process));
  _self->procedureName = R_Argument_getObjectReferenceValue(process, &argumentValues[2], _Arcadia_String_getType(process));
  _self->procedureParameters = R_Argument_getObjectReferenceValue(process, &argumentValues[3], _R_List_getType(process));
  _self->procedureBody = R_Argument_getObjectReferenceValueOrNull(process, &argumentValues[4], _R_List_getType(process));
  Arcadia_Object_setType(process, _self, _type);
}

static void
R_Mil_ProcedureDefinitionAst_visit
  (
    Arcadia_Process* process,
    R_Mil_ProcedureDefinitionAst* self
  )
{
  if (self->nativeName) {
    Arcadia_Object_visit(process, self->nativeName);
  }
  Arcadia_Object_visit(process, self->procedureName);
  Arcadia_Object_visit(process, self->procedureParameters);
  if (self->procedureBody) {
    Arcadia_Object_visit(process, self->procedureBody);
  }
}

R_Mil_ProcedureDefinitionAst*
R_Mil_ProcedureDefinitionAst_create
  (
    Arcadia_Process* process,
    Arcadia_BooleanValue entry,
    Arcadia_String* nativeName,
    Arcadia_String* procedureName,
    R_List* procedureParameters,
    R_List* procedureBody
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Boolean, .booleanValue = entry },
                               {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void },
                               {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = procedureName },
                               {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = procedureParameters },
                               {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void }, };
  if (nativeName) {
    Arcadia_Value_setObjectReferenceValue(&argumentValues[1], nativeName);
  }
  if (procedureBody) {
    Arcadia_Value_setObjectReferenceValue(&argumentValues[4], procedureBody);
  }
  R_Mil_ProcedureDefinitionAst* self = R_allocateObject(process, _R_Mil_ProcedureDefinitionAst_getType(process), 5, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
